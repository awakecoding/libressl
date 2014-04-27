
set(MODULE_NAME "ssl-headers")
set(MODULE_PREFIX "SSL_HEADERS")

project(${MODULE_NAME} C)

set(SSL_SRC "${CMAKE_SOURCE_DIR}/src")

set(SSL_INCLUDE "${CMAKE_BINARY_DIR}/include")
include_directories(${SSL_INCLUDE})

set(${MODULE_PREFIX}_SSL_HEADERS
	${SSL_SRC}/ssl/srtp.h
	${SSL_SRC}/ssl/ssl.h
	${SSL_SRC}/ssl/ssl2.h
	${SSL_SRC}/ssl/ssl3.h
	${SSL_SRC}/ssl/ssl23.h
	${SSL_SRC}/ssl/tls1.h
	${SSL_SRC}/ssl/dtls1.h
	${SSL_SRC}/ssl/kssl.h)

set(${MODULE_PREFIX}_CRYPTO_HEADERS
	${SSL_SRC}/crypto/objects/objects.h
	${SSL_SRC}/crypto/stack/safestack.h
	${SSL_SRC}/crypto/stack/stack.h
	${SSL_SRC}/crypto/buffer/buffer.h
	${SSL_SRC}/crypto/bf/blowfish.h
	${SSL_SRC}/crypto/comp/comp.h
	${SSL_SRC}/crypto/bio/bio.h
	${SSL_SRC}/crypto/bn/bn.h
	${SSL_SRC}/crypto/camellia/camellia.h
	${SSL_SRC}/crypto/cast/cast.h
	${SSL_SRC}/crypto/cmac/cmac.h
	${SSL_SRC}/crypto/cms/cms.h
	${SSL_SRC}/crypto/dh/dh.h
	${SSL_SRC}/crypto/rsa/rsa.h
	${SSL_SRC}/crypto/asn1/asn1.h
	${SSL_SRC}/crypto/asn1/asn1t.h
	${SSL_SRC}/crypto/asn1/asn1_mac.h
	${SSL_SRC}/crypto/krb5/krb5_asn.h
	${SSL_SRC}/crypto/dsa/dsa.h
	${SSL_SRC}/crypto/dso/dso.h
	${SSL_SRC}/crypto/evp/evp.h
	${SSL_SRC}/crypto/ec/ec.h
	${SSL_SRC}/crypto/ecdsa/ecdsa.h
	${SSL_SRC}/crypto/ecdh/ecdh.h
	${SSL_SRC}/crypto/sha/sha.h
	${SSL_SRC}/crypto/err/err.h
	${SSL_SRC}/crypto/lhash/lhash.h
	${SSL_SRC}/crypto/rand/rand.h
	${SSL_SRC}/crypto/x509/x509.h
	${SSL_SRC}/crypto/x509/x509_vfy.h
	${SSL_SRC}/crypto/x509v3/x509v3.h
	${SSL_SRC}/crypto/pkcs7/pkcs7.h
	${SSL_SRC}/crypto/pkcs12/pkcs12.h
	${SSL_SRC}/crypto/rc2/rc2.h
	${SSL_SRC}/crypto/rc4/rc4.h
	${SSL_SRC}/crypto/md4/md4.h
	${SSL_SRC}/crypto/md5/md5.h
	${SSL_SRC}/crypto/mdc2/mdc2.h
	${SSL_SRC}/crypto/ripemd/ripemd.h
	${SSL_SRC}/crypto/des/des.h
	${SSL_SRC}/crypto/aes/aes.h
	${SSL_SRC}/crypto/pem/pem.h
	${SSL_SRC}/crypto/pem/pem2.h
	${SSL_SRC}/crypto/hmac/hmac.h
	${SSL_SRC}/crypto/pqueue/pqueue.h
	${SSL_SRC}/crypto/engine/engine.h
	${SSL_SRC}/crypto/whrlpool/whrlpool.h
	${SSL_SRC}/crypto/txt_db/txt_db.h
	${SSL_SRC}/crypto/ui/ui.h
	${SSL_SRC}/crypto/ui/ui_compat.h
	${SSL_SRC}/crypto/ts/ts.h
	${SSL_SRC}/crypto/srp/srp.h
	${SSL_SRC}/crypto/ocsp/ocsp.h
	${SSL_SRC}/crypto/conf/conf.h
	${SSL_SRC}/crypto/conf/conf_api.h
	${SSL_SRC}/crypto/modes/modes.h
	${SSL_SRC}/crypto/crypto.h
	${SSL_SRC}/crypto/opensslv.h
	${SSL_SRC}/crypto/ossl_typ.h
	${SSL_SRC}/ssl/ssl.h
	${SSL_SRC}/e_os2.h)

set(${MODULE_PREFIX}_HEADERS
	${${MODULE_PREFIX}_SSL_HEADERS}
	${${MODULE_PREFIX}_CRYPTO_HEADERS})

add_custom_target(ssl_include_headers DEPENDS ssl-include-headers)

add_custom_command(OUTPUT ssl-include-headers
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SSL_INCLUDE}/openssl"
	COMMENT "Creating ${SSL_INCLUDE}/openssl")

foreach(INCLUDE_HEADER ${${MODULE_PREFIX}_HEADERS})
	get_filename_component(INCLUDE_HEADER_FILE ${INCLUDE_HEADER} NAME)
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${INCLUDE_HEADER}" "${SSL_INCLUDE}/openssl/${INCLUDE_HEADER_FILE}"
		COMMENT "Copying ${INCLUDE_HEADER_FILE}")
	list(APPEND SSL_INSTALL_HEADERS "${SSL_INCLUDE}/openssl/${INCLUDE_HEADER_FILE}")
endforeach()

set(SSL_OBJECTS_DIR "${CMAKE_SOURCE_DIR}/src/crypto/objects")
list(APPEND SSL_INSTALL_HEADERS "${SSL_INCLUDE}/openssl/obj_mac.h")

if(PERL_FOUND)
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${PERL_EXECUTABLE} "${SSL_OBJECTS_DIR}/objects.pl" "${SSL_OBJECTS_DIR}/objects.txt" "${SSL_OBJECTS_DIR}/obj_mac.num" "${SSL_OBJECTS_DIR}/obj_mac.h"
		COMMENT "Generating obj_mac.h")
	
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${SSL_OBJECTS_DIR}/obj_mac.h" "${SSL_INCLUDE}/openssl/obj_mac.h"
		COMMENT "Copying generated obj_mac.h")
	
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${PERL_EXECUTABLE} "${SSL_OBJECTS_DIR}/obj_dat.pl" "${SSL_OBJECTS_DIR}/obj_mac.h" "${SSL_OBJECTS_DIR}/obj_dat.h"
		COMMENT "Generating obj_dat.h")
		
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${SSL_OBJECTS_DIR}/obj_dat.h" "${SSL_INCLUDE}/openssl/obj_dat.h"
		COMMENT "Copying generated obj_dat.h")
else(PERL_FOUND)
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/ssl/obj_mac.h" "${SSL_INCLUDE}/openssl/obj_mac.h"
		COMMENT "Copying pre-generated obj_mac.h (install perl to generate)")
		
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/ssl/obj_dat.h" "${SSL_INCLUDE}/openssl/obj_dat.h"
		COMMENT "Copying pre-generated obj_dat.h (install perl to generate)")
endif(PERL_FOUND)

install(FILES ${SSL_INSTALL_HEADERS} DESTINATION include/openssl)

set(SSL_PC_VERSION "24.0")

configure_file(${CMAKE_SOURCE_DIR}/ssl/libssl.pc.in ${CMAKE_BINARY_DIR}/libssl.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libssl.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

configure_file(${CMAKE_SOURCE_DIR}/ssl/openssl.pc.in ${CMAKE_BINARY_DIR}/openssl.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/openssl.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
