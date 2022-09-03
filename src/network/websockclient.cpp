#include "../headers/gamepch.h"

WebsockClient::WebsockClient(Game *game) : mGame(game), mPID(0), mLastPacketTime(0.)
{
    // mReplicationManager = nullptr;
    mReplicationManager = new ReplicationManager(game);
    mState = ST_UNINITIALIZED;
    mPlayerID = 0;
    helloPacketSent = false;
    connected = false;
}

WebsockClient::~WebsockClient()
{
}

WebsockClient *WebsockClient::sInstance = nullptr;

bool WebsockClient::staticInit(Game *game, int pid, char *name)
{
    WebsockClient::sInstance = new WebsockClient(game);
    return WebsockClient::sInstance->init("ws://192.168.8.101:3002", pid, std::string(name));
    // return WebsockClient::sInstance->init("ws://3.104.94.74:3002", pid, std::string(name));
}

void WebsockClient::sendOutgoing()
{
    switch (mState)
    {
    case ST_UNINITIALIZED:
        break;
    case ST_SAYINGHELLO:
        if (!helloPacketSent && connected)
            sendHelloPacket();
        break;
    case ST_WELCOMED:
        sendInputPacket();
        break;
    default:
        break;
    }
}

void WebsockClient::processPacket(InputStream &inputStream)
{
    uint32_t packetType(0);
    inputStream.read(packetType);

    if (Game::DEBUG)
        printf("WebsockClient::processpacket packetType: %u, %u\n", packetType, kWelcomeCC);

    switch (packetType)
    {
    case kWelcomeCC:
        handleWelcomePacket(inputStream);
        break;
    case kStateCC:
        handleStatePacket(inputStream);
        break;
    default:
        break;
    }

    if (Game::DEBUG)
        printf("WebsockClient::processpacket Bytes remaining: %u\n", inputStream.getRemainingBitCount());
}

bool WebsockClient::init(std::string address, int pid, std::string name)
{
    mState = ST_SAYINGHELLO;
    mName = name;
    mPID = pid;

    if (!emscripten_websocket_is_supported())
        return false;

    EmscriptenWebSocketCreateAttributes ws_attr{
        address.c_str(), NULL, EM_TRUE};

    mSocket = emscripten_websocket_new(&ws_attr);

    emscripten_websocket_set_onopen_callback(mSocket, NULL, WebsockClient::onOpen);
    emscripten_websocket_set_onerror_callback(mSocket, NULL, WebsockClient::onError);
    emscripten_websocket_set_onclose_callback(mSocket, NULL, WebsockClient::onClose);
    emscripten_websocket_set_onmessage_callback(mSocket, NULL, WebsockClient::onMessage);

    return true;
}

void WebsockClient::sendHelloPacket()
{
    OutputStream helloPacket;

    helloPacket.write(kHelloCC);
    helloPacket.write(std::to_string(mPID));
    helloPacket.write(mName);

    sendMessage(helloPacket);
    helloPacketSent = true;
}

void WebsockClient::handleWelcomePacket(InputStream &inputStream)
{

    if (mState == ST_SAYINGHELLO)
    {
        uint32_t playerId(0);
        inputStream.read(playerId);

        if (Game::DEBUG)
            printf("handleWelcomePacket playerId: %u  inputStream: %s\n", playerId, inputStream.getBufferPtr());

        mPlayerID = playerId;
        mState = ST_WELCOMED;
    }
}

void WebsockClient::handleStatePacket(InputStream &inputStream)
{

    if (mState == ST_WELCOMED)
    {
        mReplicationManager->read(inputStream);
    }
}

void WebsockClient::processAllPackets()
{
    while (!mPacketQueue.empty())
    {
        mReceivedPacket &packet = mPacketQueue.front();
        processPacket(packet.getInStream());
        mPacketQueue.pop();
    }
}

void WebsockClient::setOutgoing(OutputStream *out)
{
    mOutPackets.push_back(out);
}

void WebsockClient::sendInputPacket()
{
    if ((mGame->getCurrentTime() - mLastPacketTime) > 60)
    {
        for (auto out : mOutPackets)
        {
            sendMessage(*out);
        }
    }
    mOutPackets.clear();
}

EM_BOOL WebsockClient::onOpen(int eventType, const EmscriptenWebSocketOpenEvent *websockEvent, void *userData)
{
    puts("Connected to the game server\n");
    WebsockClient::sInstance->connected = true;
    return EM_TRUE;
}

EM_BOOL WebsockClient::onError(int eventType, const EmscriptenWebSocketErrorEvent *websockEvent, void *userData)
{
    puts("Error\n");
    return EM_TRUE;
}

EM_BOOL WebsockClient::onClose(int eventType, const EmscriptenWebSocketCloseEvent *websockEvent, void *userData)
{
    puts("Connection closed\n");
    return EM_TRUE;
}

EM_BOOL WebsockClient::onMessage(int eventType, const EmscriptenWebSocketMessageEvent *websockEvent, void *userData)
{

    unsigned char *packet = static_cast<unsigned char *>(websockEvent->data);
    InputStream *inStream = new InputStream(packet, websockEvent->numBytes * 8);
    mReceivedPacket recvPacket(*inStream);

    if (Game::DEBUG)
        printf("onMessage: %s, packet: %s, numBytes: %u\n", inStream->getBufferPtr(), packet, websockEvent->numBytes);

    WebsockClient::sInstance->mPacketQueue.emplace(recvPacket);

    return EM_TRUE;
}

EM_BOOL WebsockClient::sendMessage(OutputStream &out)
{

    if (WebsockClient::sInstance->connected)
    {
        emscripten_websocket_send_binary(WebsockClient::sInstance->mSocket, (void *)out.getBufferPtr(), out.getByteLength());
        return EM_TRUE;
    }
    return EM_FALSE;
}