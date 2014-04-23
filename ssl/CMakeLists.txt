
set(MODULE_NAME "ssl")
set(MODULE_PREFIX "SSL")

project(${MODULE_NAME} C)

set(SSL_SRC "${CMAKE_SOURCE_DIR}/src")
set(LSSL_SRC "${CMAKE_SOURCE_DIR}/src/ssl")

add_definitions(-DTERMIOS)
add_definitions(-DANSI_SOURCE)
add_definitions(-DOPENSSL_NO_RC5)
add_definitions(-DOPENSSL_NO_KRB5)

set(SSL_INCLUDE "${CMAKE_BINARY_DIR}/include")
include_directories(${SSL_INCLUDE})

set(${MODULE_PREFIX}_HEADERS
	${LSSL_SRC}/srtp.h
	${LSSL_SRC}/ssl.h
	${LSSL_SRC}/ssl2.h
	${LSSL_SRC}/ssl3.h
	${LSSL_SRC}/ssl23.h
	${LSSL_SRC}/tls1.h
	${LSSL_SRC}/dtls1.h
	${LSSL_SRC}/kssl.h)

set(${MODULE_PREFIX}_SOURCES
	${LSSL_SRC}/s3_meth.c
	${LSSL_SRC}/s3_srvr.c
	${LSSL_SRC}/s3_clnt.c
	${LSSL_SRC}/s3_lib.c
	${LSSL_SRC}/s3_enc.c
	${LSSL_SRC}/s3_pkt.c
	${LSSL_SRC}/s3_both.c
	${LSSL_SRC}/s23_meth.c
	${LSSL_SRC}/s23_srvr.c
	${LSSL_SRC}/s23_clnt.c
	${LSSL_SRC}/s23_lib.c
	${LSSL_SRC}/s23_pkt.c
	${LSSL_SRC}/t1_meth.c
	${LSSL_SRC}/t1_srvr.c
	${LSSL_SRC}/t1_clnt.c
	${LSSL_SRC}/t1_lib.c
	${LSSL_SRC}/t1_enc.c
	${LSSL_SRC}/d1_meth.c
	${LSSL_SRC}/d1_srvr.c
	${LSSL_SRC}/d1_clnt.c
	${LSSL_SRC}/d1_lib.c
	${LSSL_SRC}/d1_pkt.c
	${LSSL_SRC}/d1_both.c
	${LSSL_SRC}/d1_enc.c
	${LSSL_SRC}/d1_srtp.c
	${LSSL_SRC}/ssl_lib.c
	${LSSL_SRC}/ssl_err2.c
	${LSSL_SRC}/ssl_cert.c
	${LSSL_SRC}/ssl_sess.c
	${LSSL_SRC}/ssl_ciph.c
	${LSSL_SRC}/ssl_stat.c
	${LSSL_SRC}/ssl_rsa.c
	${LSSL_SRC}/ssl_asn1.c
	${LSSL_SRC}/ssl_txt.c
	${LSSL_SRC}/ssl_algs.c
	${LSSL_SRC}/bio_ssl.c
	${LSSL_SRC}/ssl_err.c
	${LSSL_SRC}/kssl.c
	${LSSL_SRC}/tls_srp.c
	${LSSL_SRC}/t1_reneg.c
	${LSSL_SRC}/s3_cbc.c)
	
set(${MODULE_PREFIX}_INCLUDE_HEADERS
	${${MODULE_PREFIX}_HEADERS}
	${SSL_SRC}/crypto/objects/objects.h
	${SSL_SRC}/crypto/stack/safestack.h
	${SSL_SRC}/crypto/stack/stack.h
	${SSL_SRC}/crypto/buffer/buffer.h
	${SSL_SRC}/crypto/comp/comp.h
	${SSL_SRC}/crypto/bio/bio.h
	${SSL_SRC}/crypto/bn/bn.h
	${SSL_SRC}/crypto/dh/dh.h
	${SSL_SRC}/crypto/rsa/rsa.h
	${SSL_SRC}/crypto/asn1/asn1.h
	${SSL_SRC}/crypto/asn1/asn1_mac.h
	${SSL_SRC}/crypto/krb5/krb5_asn.h
	${SSL_SRC}/crypto/dsa/dsa.h
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
	${SSL_SRC}/crypto/md5/md5.h
	${SSL_SRC}/crypto/pem/pem.h
	${SSL_SRC}/crypto/pem/pem2.h
	${SSL_SRC}/crypto/hmac/hmac.h
	${SSL_SRC}/crypto/pqueue/pqueue.h
	${SSL_SRC}/crypto/engine/engine.h
	${SSL_SRC}/crypto/ui/ui.h
	${SSL_SRC}/crypto/srp/srp.h
	${SSL_SRC}/crypto/ocsp/ocsp.h
	${SSL_SRC}/crypto/conf/conf.h
	${SSL_SRC}/crypto/crypto.h
	${SSL_SRC}/crypto/opensslv.h
	${SSL_SRC}/crypto/ossl_typ.h
	${SSL_SRC}/e_os2.h)
	
add_library(${MODULE_NAME} ${${MODULE_PREFIX}_HEADERS} ${${MODULE_PREFIX}_SOURCES})

add_custom_target(ssl_include_headers DEPENDS ssl-include-headers)

add_custom_command(OUTPUT ssl-include-headers
	COMMAND ${CMAKE_COMMAND} -E make_directory "${SSL_INCLUDE}/openssl"
	COMMENT "Creating ${SSL_INCLUDE}/openssl")

foreach(INCLUDE_HEADER ${${MODULE_PREFIX}_INCLUDE_HEADERS})
	get_filename_component(INCLUDE_HEADER_FILE ${INCLUDE_HEADER} NAME)
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${CMAKE_COMMAND} -E copy "${INCLUDE_HEADER}" "${SSL_INCLUDE}/openssl/${INCLUDE_HEADER_FILE}"
		COMMENT "Copying ${INCLUDE_HEADER}")
endforeach()

set(SSL_OBJECTS_DIR "${CMAKE_SOURCE_DIR}/src/crypto/objects")

if(PERL_FOUND)
	add_custom_command(TARGET ssl_include_headers
		COMMAND ${PERL_EXECUTABLE} "${SSL_OBJECTS_DIR}/objects.pl" "${SSL_OBJECTS_DIR}/objects.txt" "${SSL_OBJECTS_DIR}/obj_mac.num" "${SSL_INCLUDE}/openssl/obj_mac.h"
		COMMENT "Generating obj_mac.h")
else(PERL_FOUND)
	add_custom_command(TARGET ssl_include_headers
		COMMAND cp "${CMAKE_SOURCE_DIR}/ssl/obj_mac.h" "${SSL_INCLUDE}/openssl/${INCLUDE_HEADER_FILE}"
		COMMENT "Copying pre-generated obj_mac.h (install perl to generate)")
endif(PERL_FOUND)

configure_file(${CMAKE_SOURCE_DIR}/ssl/opensslconf.h.in "${SSL_INCLUDE}/openssl/opensslconf.h" @ONLY)

add_dependencies(${MODULE_NAME} ssl_include_headers)

install(TARGETS ${MODULE_NAME} DESTINATION "${CMAKE_INSTALL_LIBDIR}")
