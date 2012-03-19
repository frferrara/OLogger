add_library( OLogger SHARED OLogger.cpp )

install( TARGETS OLogger DESTINATION lib )
install( FILES ${PROJECT_SOURCE_DIR}/OLogger/OLogger.hpp DESTINATION include )
