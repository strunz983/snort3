set (FLOW_INCLUDES
    expect_cache.h
    flow.h
    flow_key.h
    flow_stash.h
    stash_item.h
)

add_library (flow OBJECT
    ${FLOW_INCLUDES}
    expect_cache.cc
    flow.cc
    flow_cache.cc
    flow_cache.h
    flow_config.h
    flow_control.cc
    flow_control.h
    flow_key.cc
    flow_stash.h
    flow_stash.cc
    ha.cc
    ha.h
    ha_module.cc
    ha_module.h
    prune_stats.h
    session.h
    stash_item.h
)

install(FILES ${FLOW_INCLUDES}
    DESTINATION ${INCLUDE_INSTALL_PATH}/flow
)

add_subdirectory(test)
