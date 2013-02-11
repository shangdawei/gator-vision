

#if defined(GPIO_CONFIG)

//                Port  Pin   GPIO Mode      GPIO Speed        GPIO OType     GPIO PuPd         GPIO AF
GPIO_CONFIG(      C,    6,    GPIO_Mode_OUT, GPIO_Speed_2MHz,  GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_AF_TIM1      )


#elif defined (GPIO_CONFIG_EVAL)

//                Port  Pin   GPIO Mode      GPIO Speed        GPIO OType     GPIO PuPd         GPIO AF
GPIO_CONFIG_EVAL( G,    8,    GPIO_Mode_OUT, GPIO_Speed_2MHz,  GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_AF_TIM1      )


#else


#endif
