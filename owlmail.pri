UTILS = lib/petroules-utilities-qt/petroules-utilities.pri

!include($$UTILS) {
    message(Retrieving Git submodules...)
	$$system(git submodule init && git submodule update)

	include($$UTILS) {
		error(There was a problem attempting to retrieve the Git submodules)
	}
}
