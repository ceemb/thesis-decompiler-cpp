#ifndef MESSAGE_FACTORY_H_
#define MESSAGE_FACTORY_H_

#include <memory>
#include "global_gnb_id.h"


class XNAP_XnAP_PDU;

namespace xnap {

class Message;

class MessageFactory {

public:
	static Message* Create(const XNAP_XnAP_PDU& xnapPdu);
};

} // namespace xnap

#endif // MESSAGE_FACTORY_H_
