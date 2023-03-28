#pragma once

#include "require.h"


namespace environment
{
	namespace virtualization
	{
		bool vbox();
        bool vmware();
		bool vmware_tools();
		bool tsc_register();
		bool vmware_drivers();
		bool vmware_services();
	}

	namespace anti_debugging
	{
		bool debug_port();
		bool debug_object();
		bool debug_inherit();
		bool info_class();
		bool remote_debuger();
		bool debuger_present();
		bool being_debuged();
	}

    namespace utils
    {
		BOOL self_delete();
    }
}