#include "../inc/message_base.h"

namespace xnap {

Message::Message(MessageType messageType): messageType(messageType) {} // chained constructor call

MessageType Message::GetMessageType() const {return messageType;}

} // namespace xnap