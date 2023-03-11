#include <zmq.hpp>
#include <kproto/ipc.hpp>

using msg_t = kiq::platform_request;

msg_t make_message()
{
  return kiq::platform_request{"kiq", "1", "logicp", "Hello", "{}"};
}

void send(zmq::socket_t& socket, msg_t msg)
{
  const auto&  payload   = msg.data();
  const size_t frame_num = payload.size();

  for (int i = 0; i < frame_num; i++)
  {
    int  flag = i == (frame_num - 1) ? 0 : ZMQ_SNDMORE;
    auto data = payload.at(i);

    zmq::message_t message{data.size()};
    std::memcpy(message.data(), data.data(), data.size());

    socket.send(message, flag);
  }
}

int main(int argc, char* argv[])
{
  std::string    addr = argv[1];
  zmq::context_t ctx{1};
  zmq::socket_t  socket{ctx, ZMQ_DEALER};
  socket.connect(addr);

  send(socket, make_message());

  socket.disconnect(addr);

  return 0;
}