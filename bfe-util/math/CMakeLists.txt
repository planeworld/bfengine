INCLUDE_DIRECTORIES(.)

SET(HDRS
    adams_bashforth_integrator.h
    adams_bashforth_integrator.tpp
    adams_moulton_integrator.h
    adams_moulton_integrator.tpp
    euler_integrator.h
    euler_integrator.tpp
    integrator.h
    math_constants.h
)

INSTALL (FILES ${HDRS} DESTINATION include)
