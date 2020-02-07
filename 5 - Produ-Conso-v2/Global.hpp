#pragma once

#include <mutex>

class Global
{
public:

	static std::mutex coutMutex_;
	static std::mutex waitMutex_;
	
};