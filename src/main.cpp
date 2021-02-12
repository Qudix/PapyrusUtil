#include "Plugin.h"
#include "Data.h"
#include "Serialize.h"

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	auto path = logger::log_directory();
	if (!path) {
		return false;
	}

	*path /= "PapyrusUtil.log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);

	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = "PapyrusUtil";
	a_info->version = Version::MAJOR;

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical("Unsupported runtime version {}"sv, ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	logger::info("Loading Version: {}"sv, Version::MAJOR);

	SKSE::Init(a_skse);

	Data::InitLists();
	Plugin::InitPlugin();

	const auto serialization = SKSE::GetSerializationInterface();
	// Dev temp
	// 	serialization->SetUniqueID(884792 + 15325);
	serialization->SetUniqueID(884715692 + 227106806);
	serialization->SetSaveCallback(Data::Serialization_Save);
	serialization->SetLoadCallback(Data::Serialization_Load);
	serialization->SetRevertCallback(Data::Serialization_Revert);
	// serialization->SetFormDeleteCallback(Data::FormDelete);

	const auto papyrus = SKSE::GetPapyrusInterface();
	papyrus->Register(Plugin::RegisterFuncs);

	return true;
}
