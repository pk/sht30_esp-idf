set(component_srcs "sht30.c")
idf_component_register(SRCS "${component_srcs}" PRIV_REQUIRES esp_driver_i2c INCLUDE_DIRS ".")