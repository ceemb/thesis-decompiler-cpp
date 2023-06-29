//C++ STL
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <string>
#include <cmath>

// Internal message representation
// #include "redacted"

// Buffer containing  XnAP-InitiatingMessage: XnAP-XnSetupRequest
std::vector<asnbyte> buffer {0x00, 0x11, ...}; // redacted

int main(int argc, char *argv[]) {
    int arg_i = 0;
    int arg_d = 0;
    int c;

    while ((c = getopt(argc, argv, "i:d:")) != -1) {
        switch (c) {
            case 'i':
                arg_i = std::atoi(optarg);
                break;
            case 'd':
                arg_d = std::atoi(optarg);
                break;
            case '?':
                if (optopt == 'i' || optopt == 'd') {
                    std::cerr << "Option -" << optopt << " requires an argument." << std::endl;
                } else {
                    std::cerr << "Unknown option -" << optopt << "." << std::endl;
                }
                return 1;
            default:
                std::abort();
        }
    }

    if (arg_i == 0 || arg_d == 0) {
        std::cerr << "Usage: " << argv[0] << " -i <int> -d <int>" << std::endl;
        return 1;
    }
	std::ofstream outputFile("output.csv");
    outputFile << "Duration Iteration, Decoding, Decompiling, decompile [%], Decode standard deviation, decompile standard deviation\n";
	struct timespec ts;
    ts.tv_sec = 0;

	// Create Asn1 context and set encoding scheme
	std::unique_ptr<asnContext> context = std::make_unique<asnContext>();
	context->setAbstractSyntax(&XNAP_AbstractSyntax);
  	context->setAutomaticDecoding(asnTRUE);
  	context->setConstraintCheckDuringDecoding(asnTRUE);
  	context->setConstraintCheckDuringEncoding(asnTRUE);

	std::chrono::time_point<std::chrono::steady_clock> start_time;
	std::chrono::time_point<std::chrono::steady_clock> decode_start_time;
	std::chrono::time_point<std::chrono::steady_clock> decode_time;
	std::chrono::time_point<std::chrono::steady_clock> decompile_time;std::chrono::time_point<std::chrono::steady_clock> end_time;

    for (int d = 0; d < arg_d; d++) {
		// ### Timestamp start ###
		std::vector<int> decoding;
		std::vector<int> decompilation;

    	start_time = std::chrono::steady_clock::now();

		for (int i = 0; i < arg_i; i++) {
			decode_start_time = std::chrono::steady_clock::now();
			// Create memory stream from buffer holding encoded message
			asnMemoryStream inputStream(buffer.data(), buffer.size(), asnFSTREAM_READ);

			// Try to decode
			auto asnMessage = new XNAP_XnAP_PDU();
			try {
				asnMessage->PERdecode(context.get(), &inputStream);
			}
			catch (const asnException& e) {
				std::cout << "Failed to decode, terminating" << std::endl;
				std::exit(0);
			}
			decode_time = std::chrono::steady_clock::now();
			auto message = xnap::MessageFactory::Create(*asnMessage);
			if (message == nullptr) {
				std::cout << "Failed to create message, terminating" << std::endl;
				std::exit(0);
			}
			decompile_time = std::chrono::steady_clock::now();
			decoding.emplace_back((std::chrono::duration_cast<std::chrono::nanoseconds>(decode_time - decode_start_time)).count());
			decompilation.emplace_back((std::chrono::duration_cast<std::chrono::nanoseconds>(decompile_time - decode_time)).count());

			delete asnMessage;
			delete message;
		}
		// ### Timestamp stop ###

		uint64_t decodeSum = 0;
		for(auto& d_ : decoding) { decodeSum += d_; }
		uint64_t decodeAvg = decodeSum / decoding.size();
		uint64_t decompSum = 0;
		for(auto& d_ : decompilation) { decompSum += d_; }
		uint64_t decompAvg = decompSum / decompilation.size();

		double decodeVariance = 0.0;
		for (int i = 1; i < arg_i; i++) {
			if (decoding[i]< 2147483647){ // LONG_MAX
				decodeVariance += pow(std::abs(decoding[i] - static_cast<int64_t>(decodeAvg)), 2);
			}
		}
		decodeVariance /= (arg_i-1);
		double decompVariance = 0.0;
		for (int i = 1; i < arg_i; i++) {
			if (decoding[i]< 2147483647){ // LONG_MAX
				decompVariance += pow(std::abs(decompilation[i] - static_cast<int64_t>(decompAvg)), 2);
			}
		}
		decompVariance /= (arg_i-1);
		outputFile << d << "," << decodeAvg << ", " << decompAvg << ", " << 100.0*decompAvg/(decodeAvg + decompAvg) << ", " << sqrt(decodeVariance) << ", " << sqrt(decompVariance) << "\n";

		end_time = std::chrono::steady_clock::now();
		ts.tv_nsec = 1000000000-((std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time)).count());
		nanosleep(&ts, NULL);
	}

	// print to output file (CSV)
    /*for (int i = 0; i < arg_d; i++)
	{
		outputFile << i << "," << duration_ns[i] << "\n";
		for (int j = 0; j < arg_i; j++)
		{
			outputFile << i << "," << "-" << ", " << j << ", " << decoding_times[i][j] << ", " << decompilation_times[i][j] << ", " << (100*decompilation_times[i][j]/(decompilation_times[i][j]+decoding_times[i][j])) << "\n";
		}
		
	}*/
	
	outputFile.close();
	// message->Print();
  	return 0;
}
