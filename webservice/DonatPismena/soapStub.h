/* soapStub.h
   Generated by gSOAP 2.8.17r from DonatPismenaService.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under one of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#ifndef soapStub_H
#define soapStub_H
#include <vector>
#define SOAP_NAMESPACE_OF_ser	"http://schemas.microsoft.com/2003/10/Serialization/"
#define SOAP_NAMESPACE_OF_ns2	"http://www.t.ht.hr/donat/pismena/service/schemas/rev1.2/"
#define SOAP_NAMESPACE_OF_ns1	"http://www.t.ht.hr/donat/pismena/service/definitions/rev1.2/"
#include "stdsoap2.h"
#if GSOAP_VERSION != 20817
# error "GSOAP VERSION MISMATCH IN GENERATED CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE_xsd__duration
#define SOAP_TYPE_xsd__duration (20)
typedef LONG64 xsd__duration;
#endif
#ifndef SOAP_TYPE_xsd__QName
#define SOAP_TYPE_xsd__QName (11)
typedef std::string xsd__QName;
#endif


/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_xsd__anyType
#define SOAP_TYPE_xsd__anyType (8)
/* Primitive xsd:anyType schema type: */
class SOAP_CMAC xsd__anyType
{
public:
	char *__item;
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 8; } /* = unique type id SOAP_TYPE_xsd__anyType */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__anyType() { xsd__anyType::soap_default(NULL); }
	virtual ~xsd__anyType() { }
};
#endif

#if 0 /* volatile type: do not declare here, declared elsewhere */

#endif

#ifndef SOAP_TYPE_xsd__base64Binary
#define SOAP_TYPE_xsd__base64Binary (12)
/* Base64 schema type: */
class SOAP_CMAC xsd__base64Binary
{
public:
	unsigned char *__ptr;
	int __size;
	char *id;	/* optional element of type xsd:string */
	char *type;	/* optional element of type xsd:string */
	char *options;	/* optional element of type xsd:string */
	struct soap *soap;	/* transient */
public:
	virtual int soap_type() const { return 12; } /* = unique type id SOAP_TYPE_xsd__base64Binary */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__base64Binary() { xsd__base64Binary::soap_default(NULL); }
	virtual ~xsd__base64Binary() { }
};
#endif

#ifndef SOAP_TYPE_xsd__ID_
#define SOAP_TYPE_xsd__ID_ (23)
/* Primitive xsd:ID schema type: */
class SOAP_CMAC xsd__ID_ : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 23; } /* = unique type id SOAP_TYPE_xsd__ID_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__ID_() { xsd__ID_::soap_default(NULL); }
	virtual ~xsd__ID_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__IDREF_
#define SOAP_TYPE_xsd__IDREF_ (25)
/* Primitive xsd:IDREF schema type: */
class SOAP_CMAC xsd__IDREF_ : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 25; } /* = unique type id SOAP_TYPE_xsd__IDREF_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__IDREF_() { xsd__IDREF_::soap_default(NULL); }
	virtual ~xsd__IDREF_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__QName_
#define SOAP_TYPE_xsd__QName_ (26)
/* Primitive xsd:QName schema type: */
class SOAP_CMAC xsd__QName_ : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 26; } /* = unique type id SOAP_TYPE_xsd__QName_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__QName_() { xsd__QName_::soap_default(NULL); }
	virtual ~xsd__QName_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__anyURI_
#define SOAP_TYPE_xsd__anyURI_ (28)
/* Primitive xsd:anyURI schema type: */
class SOAP_CMAC xsd__anyURI_ : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 28; } /* = unique type id SOAP_TYPE_xsd__anyURI_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__anyURI_() { xsd__anyURI_::soap_default(NULL); }
	virtual ~xsd__anyURI_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__base64Binary_
#define SOAP_TYPE_xsd__base64Binary_ (29)
/* Primitive xsd:base64Binary schema type: */
class SOAP_CMAC xsd__base64Binary_ : public xsd__anyType
{
public:
	xsd__base64Binary __item;
public:
	virtual int soap_type() const { return 29; } /* = unique type id SOAP_TYPE_xsd__base64Binary_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__base64Binary_() { xsd__base64Binary_::soap_default(NULL); }
	virtual ~xsd__base64Binary_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__boolean
#define SOAP_TYPE_xsd__boolean (30)
/* Primitive xsd:boolean schema type: */
class SOAP_CMAC xsd__boolean : public xsd__anyType
{
public:
	bool __item;
public:
	virtual int soap_type() const { return 30; } /* = unique type id SOAP_TYPE_xsd__boolean */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__boolean() { xsd__boolean::soap_default(NULL); }
	virtual ~xsd__boolean() { }
};
#endif

#ifndef SOAP_TYPE_xsd__byte_
#define SOAP_TYPE_xsd__byte_ (32)
/* Primitive xsd:byte schema type: */
class SOAP_CMAC xsd__byte_ : public xsd__anyType
{
public:
	char __item;
public:
	virtual int soap_type() const { return 32; } /* = unique type id SOAP_TYPE_xsd__byte_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__byte_() { xsd__byte_::soap_default(NULL); }
	virtual ~xsd__byte_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__dateTime
#define SOAP_TYPE_xsd__dateTime (33)
/* Primitive xsd:dateTime schema type: */
class SOAP_CMAC xsd__dateTime : public xsd__anyType
{
public:
	time_t __item;
public:
	virtual int soap_type() const { return 33; } /* = unique type id SOAP_TYPE_xsd__dateTime */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__dateTime() { xsd__dateTime::soap_default(NULL); }
	virtual ~xsd__dateTime() { }
};
#endif

#ifndef SOAP_TYPE_xsd__decimal_
#define SOAP_TYPE_xsd__decimal_ (36)
/* Primitive xsd:decimal schema type: */
class SOAP_CMAC xsd__decimal_ : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 36; } /* = unique type id SOAP_TYPE_xsd__decimal_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__decimal_() { xsd__decimal_::soap_default(NULL); }
	virtual ~xsd__decimal_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__double
#define SOAP_TYPE_xsd__double (37)
/* Primitive xsd:double schema type: */
class SOAP_CMAC xsd__double : public xsd__anyType
{
public:
	double __item;
public:
	virtual int soap_type() const { return 37; } /* = unique type id SOAP_TYPE_xsd__double */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__double() { xsd__double::soap_default(NULL); }
	virtual ~xsd__double() { }
};
#endif

#ifndef SOAP_TYPE_xsd__duration_
#define SOAP_TYPE_xsd__duration_ (39)
/* Primitive xsd:duration schema type: */
class SOAP_CMAC xsd__duration_ : public xsd__anyType
{
public:
	LONG64 __item;	/* external */
public:
	virtual int soap_type() const { return 39; } /* = unique type id SOAP_TYPE_xsd__duration_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__duration_() { xsd__duration_::soap_default(NULL); }
	virtual ~xsd__duration_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__float
#define SOAP_TYPE_xsd__float (40)
/* Primitive xsd:float schema type: */
class SOAP_CMAC xsd__float : public xsd__anyType
{
public:
	float __item;
public:
	virtual int soap_type() const { return 40; } /* = unique type id SOAP_TYPE_xsd__float */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__float() { xsd__float::soap_default(NULL); }
	virtual ~xsd__float() { }
};
#endif

#ifndef SOAP_TYPE_xsd__int
#define SOAP_TYPE_xsd__int (42)
/* Primitive xsd:int schema type: */
class SOAP_CMAC xsd__int : public xsd__anyType
{
public:
	int __item;
public:
	virtual int soap_type() const { return 42; } /* = unique type id SOAP_TYPE_xsd__int */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__int() { xsd__int::soap_default(NULL); }
	virtual ~xsd__int() { }
};
#endif

#ifndef SOAP_TYPE_xsd__long
#define SOAP_TYPE_xsd__long (43)
/* Primitive xsd:long schema type: */
class SOAP_CMAC xsd__long : public xsd__anyType
{
public:
	LONG64 __item;
public:
	virtual int soap_type() const { return 43; } /* = unique type id SOAP_TYPE_xsd__long */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__long() { xsd__long::soap_default(NULL); }
	virtual ~xsd__long() { }
};
#endif

#ifndef SOAP_TYPE_xsd__short
#define SOAP_TYPE_xsd__short (45)
/* Primitive xsd:short schema type: */
class SOAP_CMAC xsd__short : public xsd__anyType
{
public:
	short __item;
public:
	virtual int soap_type() const { return 45; } /* = unique type id SOAP_TYPE_xsd__short */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__short() { xsd__short::soap_default(NULL); }
	virtual ~xsd__short() { }
};
#endif

#ifndef SOAP_TYPE_xsd__string
#define SOAP_TYPE_xsd__string (47)
/* Primitive xsd:string schema type: */
class SOAP_CMAC xsd__string : public xsd__anyType
{
public:
	std::string __item;
public:
	virtual int soap_type() const { return 47; } /* = unique type id SOAP_TYPE_xsd__string */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__string() { xsd__string::soap_default(NULL); }
	virtual ~xsd__string() { }
};
#endif

#ifndef SOAP_TYPE_xsd__unsignedByte_
#define SOAP_TYPE_xsd__unsignedByte_ (48)
/* Primitive xsd:unsignedByte schema type: */
class SOAP_CMAC xsd__unsignedByte_ : public xsd__anyType
{
public:
	unsigned char __item;
public:
	virtual int soap_type() const { return 48; } /* = unique type id SOAP_TYPE_xsd__unsignedByte_ */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__unsignedByte_() { xsd__unsignedByte_::soap_default(NULL); }
	virtual ~xsd__unsignedByte_() { }
};
#endif

#ifndef SOAP_TYPE_xsd__unsignedInt
#define SOAP_TYPE_xsd__unsignedInt (49)
/* Primitive xsd:unsignedInt schema type: */
class SOAP_CMAC xsd__unsignedInt : public xsd__anyType
{
public:
	unsigned int __item;
public:
	virtual int soap_type() const { return 49; } /* = unique type id SOAP_TYPE_xsd__unsignedInt */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__unsignedInt() { xsd__unsignedInt::soap_default(NULL); }
	virtual ~xsd__unsignedInt() { }
};
#endif

#ifndef SOAP_TYPE_xsd__unsignedLong
#define SOAP_TYPE_xsd__unsignedLong (50)
/* Primitive xsd:unsignedLong schema type: */
class SOAP_CMAC xsd__unsignedLong : public xsd__anyType
{
public:
	ULONG64 __item;
public:
	virtual int soap_type() const { return 50; } /* = unique type id SOAP_TYPE_xsd__unsignedLong */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__unsignedLong() { xsd__unsignedLong::soap_default(NULL); }
	virtual ~xsd__unsignedLong() { }
};
#endif

#ifndef SOAP_TYPE_xsd__unsignedShort
#define SOAP_TYPE_xsd__unsignedShort (52)
/* Primitive xsd:unsignedShort schema type: */
class SOAP_CMAC xsd__unsignedShort : public xsd__anyType
{
public:
	unsigned short __item;
public:
	virtual int soap_type() const { return 52; } /* = unique type id SOAP_TYPE_xsd__unsignedShort */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         xsd__unsignedShort() { xsd__unsignedShort::soap_default(NULL); }
	virtual ~xsd__unsignedShort() { }
};
#endif

#ifndef SOAP_TYPE_ns2__DonatPismenoRequestDataContract
#define SOAP_TYPE_ns2__DonatPismenoRequestDataContract (54)
/* ns2:DonatPismenoRequestDataContract */
class SOAP_CMAC ns2__DonatPismenoRequestDataContract : public xsd__anyType
{
public:
	LONG64 *SporazumId;	/* optional element of type xsd:long */
	std::string *BrojDokumenta;	/* optional element of type xsd:string */
public:
	virtual int soap_type() const { return 54; } /* = unique type id SOAP_TYPE_ns2__DonatPismenoRequestDataContract */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns2__DonatPismenoRequestDataContract() { ns2__DonatPismenoRequestDataContract::soap_default(NULL); }
	virtual ~ns2__DonatPismenoRequestDataContract() { }
};
#endif

#ifndef SOAP_TYPE_ns2__DonatPismenoPdfDataContract
#define SOAP_TYPE_ns2__DonatPismenoPdfDataContract (55)
/* ns2:DonatPismenoPdfDataContract */
class SOAP_CMAC ns2__DonatPismenoPdfDataContract : public xsd__anyType
{
public:
	xsd__base64Binary *Pdf;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:base64Binary */
public:
	virtual int soap_type() const { return 55; } /* = unique type id SOAP_TYPE_ns2__DonatPismenoPdfDataContract */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns2__DonatPismenoPdfDataContract() { ns2__DonatPismenoPdfDataContract::soap_default(NULL); }
	virtual ~ns2__DonatPismenoPdfDataContract() { }
};
#endif

#ifndef SOAP_TYPE_ns2__DonatPismenaFaultContract
#define SOAP_TYPE_ns2__DonatPismenaFaultContract (56)
/* ns2:DonatPismenaFaultContract */
class SOAP_CMAC ns2__DonatPismenaFaultContract : public xsd__anyType
{
public:
	int *ErrorNumber;	/* optional element of type xsd:int */
	std::string *ErrorDescription;	/* optional element of type xsd:string */
public:
	virtual int soap_type() const { return 56; } /* = unique type id SOAP_TYPE_ns2__DonatPismenaFaultContract */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns2__DonatPismenaFaultContract() { ns2__DonatPismenaFaultContract::soap_default(NULL); }
	virtual ~ns2__DonatPismenaFaultContract() { }
};
#endif

#ifndef SOAP_TYPE_ns2__DonatPismenoDataContract
#define SOAP_TYPE_ns2__DonatPismenoDataContract (57)
/* ns2:DonatPismenoDataContract */
class SOAP_CMAC ns2__DonatPismenoDataContract : public xsd__anyType
{
public:
	xsd__base64Binary *Pdf;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:base64Binary */
	class ns2__DonatPismenoMetadataDataContract *MetaData;	/* optional element of type ns2:DonatPismenoMetadataDataContract */
public:
	virtual int soap_type() const { return 57; } /* = unique type id SOAP_TYPE_ns2__DonatPismenoDataContract */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns2__DonatPismenoDataContract() { ns2__DonatPismenoDataContract::soap_default(NULL); }
	virtual ~ns2__DonatPismenoDataContract() { }
};
#endif

#ifndef SOAP_TYPE_ns2__DonatPismenoMetadataDataContract
#define SOAP_TYPE_ns2__DonatPismenoMetadataDataContract (58)
/* ns2:DonatPismenoMetadataDataContract */
class SOAP_CMAC ns2__DonatPismenoMetadataDataContract : public xsd__anyType
{
public:
	std::string *Oib;	/* optional element of type xsd:string */
	std::string *JopNumber;	/* optional element of type xsd:string */
	std::string *Mb;	/* optional element of type xsd:string */
	std::string *CustomerType;	/* optional element of type xsd:string */
	std::string *CaseFileNumber;	/* optional element of type xsd:string */
	std::string *RefNo;	/* optional element of type xsd:string */
	std::string *Application;	/* optional element of type xsd:string */
	std::string *RequestCode;	/* optional element of type xsd:string */
	std::string *RequestType;	/* optional element of type xsd:string */
	std::string *DocumentType;	/* optional element of type xsd:string */
	std::string *DocumentNumber;	/* optional element of type xsd:string */
	std::string *UserName;	/* optional element of type xsd:string */
	std::string *AgentName;	/* optional element of type xsd:string */
	std::string *PartnerAddress;	/* optional element of type xsd:string */
	std::string *CustomerName;	/* optional element of type xsd:string */
	std::string *UserId1;	/* optional element of type xsd:string */
	std::string *UserId2;	/* optional element of type xsd:string */
	std::string *ContractDate;	/* optional element of type xsd:string */
	std::string *OriginalCopy;	/* optional element of type xsd:string */
	std::string *ElectronicSign;	/* optional element of type xsd:string */
	std::string *AdditionalInfo;	/* optional element of type xsd:string */
	std::string *DocumentTypeId;	/* optional element of type xsd:string */
	std::string *AccountId;	/* optional element of type xsd:string */
	std::string *ContractId;	/* optional element of type xsd:string */
	std::string *Kp;	/* optional element of type xsd:string */
	std::string *StrankaId;	/* optional element of type xsd:string */
	int *Pages;	/* optional element of type xsd:int */
	std::string *FileMedia;	/* optional element of type xsd:string */
	std::string *TableSign;	/* optional element of type xsd:string */
	std::string *Pib;	/* optional element of type xsd:string */
	std::string *SalesChannel;	/* optional element of type xsd:string */
	std::string *FileNetId;	/* optional element of type xsd:string */
public:
	virtual int soap_type() const { return 58; } /* = unique type id SOAP_TYPE_ns2__DonatPismenoMetadataDataContract */
	virtual void soap_default(struct soap*);
	virtual void soap_serialize(struct soap*) const;
	virtual int soap_put(struct soap*, const char*, const char*) const;
	virtual int soap_out(struct soap*, const char*, int, const char*) const;
	virtual void *soap_get(struct soap*, const char*, const char*);
	virtual void *soap_in(struct soap*, const char*, const char*);
	         ns2__DonatPismenoMetadataDataContract() { ns2__DonatPismenoMetadataDataContract::soap_default(NULL); }
	virtual ~ns2__DonatPismenoMetadataDataContract() { }
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (64)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
public:
	char *__any;
	ns2__DonatPismenaFaultContract *ns2__DonatPismenaFaultContract_;	/* optional element of type ns2:DonatPismenaFaultContract */
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
public:
	int soap_type() const { return 64; } /* = unique type id SOAP_TYPE_SOAP_ENV__Detail */
};
#endif

#endif

#ifndef SOAP_TYPE___ns1__GetZahtjevPdf
#define SOAP_TYPE___ns1__GetZahtjevPdf (71)
/* Operation wrapper: */
struct __ns1__GetZahtjevPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatZahtjevReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 71; } /* = unique type id SOAP_TYPE___ns1__GetZahtjevPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetZahtjev
#define SOAP_TYPE___ns1__GetZahtjev (74)
/* Operation wrapper: */
struct __ns1__GetZahtjev
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatZahtjevReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 74; } /* = unique type id SOAP_TYPE___ns1__GetZahtjev */
};
#endif

#ifndef SOAP_TYPE___ns1__GetUgovorPdf
#define SOAP_TYPE___ns1__GetUgovorPdf (76)
/* Operation wrapper: */
struct __ns1__GetUgovorPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatUgovorReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 76; } /* = unique type id SOAP_TYPE___ns1__GetUgovorPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetUgovor
#define SOAP_TYPE___ns1__GetUgovor (78)
/* Operation wrapper: */
struct __ns1__GetUgovor
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatUgovorReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 78; } /* = unique type id SOAP_TYPE___ns1__GetUgovor */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPrivolaPdf
#define SOAP_TYPE___ns1__GetPrivolaPdf (80)
/* Operation wrapper: */
struct __ns1__GetPrivolaPdf
{
public:
	LONG64 ns1__KupacId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 80; } /* = unique type id SOAP_TYPE___ns1__GetPrivolaPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPrivola
#define SOAP_TYPE___ns1__GetPrivola (82)
/* Operation wrapper: */
struct __ns1__GetPrivola
{
public:
	LONG64 ns1__KupacId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 82; } /* = unique type id SOAP_TYPE___ns1__GetPrivola */
};
#endif

#ifndef SOAP_TYPE___ns1__GetObavijestPdf
#define SOAP_TYPE___ns1__GetObavijestPdf (84)
/* Operation wrapper: */
struct __ns1__GetObavijestPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatObavijestReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 84; } /* = unique type id SOAP_TYPE___ns1__GetObavijestPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetObavijest
#define SOAP_TYPE___ns1__GetObavijest (86)
/* Operation wrapper: */
struct __ns1__GetObavijest
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatObavijestReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 86; } /* = unique type id SOAP_TYPE___ns1__GetObavijest */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPismoPdf
#define SOAP_TYPE___ns1__GetPismoPdf (88)
/* Operation wrapper: */
struct __ns1__GetPismoPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatPismoReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 88; } /* = unique type id SOAP_TYPE___ns1__GetPismoPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPismo
#define SOAP_TYPE___ns1__GetPismo (90)
/* Operation wrapper: */
struct __ns1__GetPismo
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatPismoReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 90; } /* = unique type id SOAP_TYPE___ns1__GetPismo */
};
#endif

#ifndef SOAP_TYPE___ns1__GetOdbijenicaPdf
#define SOAP_TYPE___ns1__GetOdbijenicaPdf (92)
/* Operation wrapper: */
struct __ns1__GetOdbijenicaPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatOdbijenicaReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 92; } /* = unique type id SOAP_TYPE___ns1__GetOdbijenicaPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetOdbijenica
#define SOAP_TYPE___ns1__GetOdbijenica (94)
/* Operation wrapper: */
struct __ns1__GetOdbijenica
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatOdbijenicaReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 94; } /* = unique type id SOAP_TYPE___ns1__GetOdbijenica */
};
#endif

#ifndef SOAP_TYPE___ns1__GetUgovornaObvezaPdf
#define SOAP_TYPE___ns1__GetUgovornaObvezaPdf (96)
/* Operation wrapper: */
struct __ns1__GetUgovornaObvezaPdf
{
public:
	LONG64 ns1__GrupaImovineId;	/* required element of type xsd:long */
	LONG64 ns1__KupacId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 96; } /* = unique type id SOAP_TYPE___ns1__GetUgovornaObvezaPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetUgovornaObveza
#define SOAP_TYPE___ns1__GetUgovornaObveza (98)
/* Operation wrapper: */
struct __ns1__GetUgovornaObveza
{
public:
	LONG64 ns1__GrupaImovineId;	/* required element of type xsd:long */
	LONG64 ns1__KupacId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 98; } /* = unique type id SOAP_TYPE___ns1__GetUgovornaObveza */
};
#endif

#ifndef SOAP_TYPE___ns1__GetTrajniNalogPdf
#define SOAP_TYPE___ns1__GetTrajniNalogPdf (100)
/* Operation wrapper: */
struct __ns1__GetTrajniNalogPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatTrajniNalogReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 100; } /* = unique type id SOAP_TYPE___ns1__GetTrajniNalogPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetTrajniNalog
#define SOAP_TYPE___ns1__GetTrajniNalog (102)
/* Operation wrapper: */
struct __ns1__GetTrajniNalog
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatTrajniNalogReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 102; } /* = unique type id SOAP_TYPE___ns1__GetTrajniNalog */
};
#endif

#ifndef SOAP_TYPE___ns1__GetSplitContractPdf
#define SOAP_TYPE___ns1__GetSplitContractPdf (104)
/* Operation wrapper: */
struct __ns1__GetSplitContractPdf
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatSplitContractReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 104; } /* = unique type id SOAP_TYPE___ns1__GetSplitContractPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetSplitContract
#define SOAP_TYPE___ns1__GetSplitContract (106)
/* Operation wrapper: */
struct __ns1__GetSplitContract
{
public:
	ns2__DonatPismenoRequestDataContract *ns1__DonatSplitContractReq;	/* optional element of type ns2:DonatPismenoRequestDataContract */
public:
	int soap_type() const { return 106; } /* = unique type id SOAP_TYPE___ns1__GetSplitContract */
};
#endif

#ifndef SOAP_TYPE___ns1__GetZlonamjerniPdf
#define SOAP_TYPE___ns1__GetZlonamjerniPdf (108)
/* Operation wrapper: */
struct __ns1__GetZlonamjerniPdf
{
public:
	LONG64 ns1__ZlonamjerniId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 108; } /* = unique type id SOAP_TYPE___ns1__GetZlonamjerniPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetZlonamjerni
#define SOAP_TYPE___ns1__GetZlonamjerni (110)
/* Operation wrapper: */
struct __ns1__GetZlonamjerni
{
public:
	LONG64 ns1__ZlonamjerniId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 110; } /* = unique type id SOAP_TYPE___ns1__GetZlonamjerni */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPrigovorPdf
#define SOAP_TYPE___ns1__GetPrigovorPdf (112)
/* Operation wrapper: */
struct __ns1__GetPrigovorPdf
{
public:
	LONG64 ns1__PrigovorId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 112; } /* = unique type id SOAP_TYPE___ns1__GetPrigovorPdf */
};
#endif

#ifndef SOAP_TYPE___ns1__GetPrigovor
#define SOAP_TYPE___ns1__GetPrigovor (114)
/* Operation wrapper: */
struct __ns1__GetPrigovor
{
public:
	LONG64 ns1__PrigovorId;	/* required element of type xsd:long */
public:
	int soap_type() const { return 114; } /* = unique type id SOAP_TYPE___ns1__GetPrigovor */
};
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (115)
/* SOAP Header: */
struct SOAP_ENV__Header
{
public:
	int soap_type() const { return 115; } /* = unique type id SOAP_TYPE_SOAP_ENV__Header */
#ifdef WITH_NOEMPTYSTRUCT
private:
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (116)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
public:
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
public:
	int soap_type() const { return 116; } /* = unique type id SOAP_TYPE_SOAP_ENV__Code */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (118)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
public:
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
public:
	int soap_type() const { return 118; } /* = unique type id SOAP_TYPE_SOAP_ENV__Reason */
};
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (119)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
public:
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
public:
	int soap_type() const { return 119; } /* = unique type id SOAP_TYPE_SOAP_ENV__Fault */
};
#endif

#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (6)
typedef char *_XML;
#endif

#ifndef SOAP_TYPE_xsd__byte
#define SOAP_TYPE_xsd__byte (16)
typedef char xsd__byte;
#endif

#ifndef SOAP_TYPE_xsd__unsignedByte
#define SOAP_TYPE_xsd__unsignedByte (21)
typedef unsigned char xsd__unsignedByte;
#endif

#ifndef SOAP_TYPE_xsd__ID
#define SOAP_TYPE_xsd__ID (22)
typedef std::string xsd__ID;
#endif

#ifndef SOAP_TYPE_xsd__IDREF
#define SOAP_TYPE_xsd__IDREF (24)
typedef std::string xsd__IDREF;
#endif

#ifndef SOAP_TYPE_xsd__anyURI
#define SOAP_TYPE_xsd__anyURI (27)
typedef std::string xsd__anyURI;
#endif

#ifndef SOAP_TYPE_xsd__decimal
#define SOAP_TYPE_xsd__decimal (35)
typedef std::string xsd__decimal;
#endif


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#endif

/* End of soapStub.h */