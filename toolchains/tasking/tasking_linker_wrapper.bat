@ECHO OFF
SET _args=%*
SET _fixed=%_args:@=--option-file=%
external\+_repo_rules+tasking_windows\bin\ltc.exe %_fixed%
