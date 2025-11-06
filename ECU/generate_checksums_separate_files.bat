:: vsgoma:Create checksums for vflash execution on next job run 
@echo off
if "%1" == "" goto usage

echo.
echo Generate checksum (CRC32) for Vector SLP3
echo Generate signature (RSA)
echo Generate CMAC (HMAC)
echo Compress file (LZMA and LZSS compression)
echo Encrypt files (AES)
echo.
echo CRC (Security model NONE)            :
echo %~dpn1.crc
echo CMAC (Security model C)              :
echo %~dpn1_cmac.sig
echo HMAC (Security model C)              :
echo %~dpn1_hmac.sig
echo Compressed file (LZMA)               :
echo %~dpn1_lzma%~x1
echo Compressed file (LZSS)               :
echo %~dpn1_lzss%~x1
echo Encrypted file                       :
echo %~dpn1_aes%~x1
echo Encrypted and compressed file (LZMA) :
echo %~dpn1_lzma_aes%~x1
echo Encrypted and compressed file (LZSS) :
echo %~dpn1_lzss_aes%~x1
echo RSA signature (Security model CCC)   :
echo %~dpn1_ccc.rsa
echo.

set local_dir=%~dp0

:: Hexview executable
set hexview_exe=..\..\..\..\..\HexView\hexview.exe
set opt_level=9
set dict_size=4096
:: LZSS compression
set distance_offset=10
set data_length=4
:: Keys
set mac_key=%local_dir%\Demokeys\c_key.txt
set rsa_key=%local_dir%\Demokeys\ccc_key_private.txt

set aesiv=00000000000000000000000000000000
set aeskey=00112233445566778899aabbccddeeff

echo Calculate CRC...
%hexview_exe% %1 /S -e:%local_dir%error.txt /cs9:%~pn1.crc

echo Calculate CMAC (Security class C)...
%hexview_exe% %1 /S -e:%local_dir%error.txt /dp45:%mac_key%;%~dpn1_cmac.sig

echo Calculate SHA1 HMAC (Security class C)...
%hexview_exe% %1 /S -e:%local_dir%error.txt /dp5:%mac_key%;%~dpn1_hmac.sig

echo ...finished.
echo.
goto end

:usage
echo "Please call with a hex file as parameter."
pause

:end
if exist %local_dir%\error.txt del %local_dir%\error.txt
