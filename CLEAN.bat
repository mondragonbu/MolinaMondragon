rmdir /s /q Binaries
rmdir /s /q Intermediate
rmdir /s /q Saved
rmdir /s /q DerivedDataCache
rmdir /s /q Build
rmdir /s /q .vs
del **.opensdf
del **.sdf
del **.sln
del **.suo
del **.xcodeproj

@echo off
for /f "delims=" %%d in ('dir /s /b /ad ^| sort /r') do (rd "%%d" 2>NUL)