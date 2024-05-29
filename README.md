# Multithreading logger

## Build & Run

```
$ mdkir build && cd build
$ cmake ..
$ make
```
## Using 
```
   LoggerPool* logger_pool;
  logger_pool = LoggerPool::getInstance();

  logger_pool->add_logger_module("app"+APP_ID, "module1", "./output/" + moduleid + ".log",
                                    log_target_bitmask, log_level);

  logger_pool->add_logger_module("app"+APP_ID, "module2", "./output/" + moduleid + ".log",
                                    log_target_bitmask, log_level);

```
