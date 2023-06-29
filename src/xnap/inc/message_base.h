#ifndef MESSAGE_BASE_H_
#define MESSAGE_BASE_H_

namespace xnap {

enum class MessageType {
	XN_SETUP_REQUEST
};

class Message {
public:
	Message(MessageType messageType);
	virtual ~Message() = 0;

	MessageType GetMessageType() const;
	virtual void Print() const = 0;

private:
	MessageType messageType;
};

inline Message::~Message() = default;

} // namespace xnap

#endif // MESSAGE_BASE_H_