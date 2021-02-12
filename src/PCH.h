#pragma once

#include "SKSE/SKSE.h"
#include "RE/Skyrim.h"

#include <locale.h>
#include <shlobj.h>

#include <spdlog/sinks/basic_file_sink.h>

namespace WinAPI = SKSE::WinAPI;

namespace logger
{
	using namespace SKSE::log;
}

using namespace std::literals;

#define DLLEXPORT __declspec(dllexport)

#include "Version.h"