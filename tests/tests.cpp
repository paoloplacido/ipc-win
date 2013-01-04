// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include "Messages.pb.h"
#include <windows.h>
#include <assert.h>
#include <string>
#include <vector>
#include <list>
#include <stopwatch.h>
#include <objects.h>


TEST(add_hoc_deandserialization,ad_hoc_deserialize_signle_item){
}
	//custom_response r;
	//r.m_data.insert(r.m_data.end()," ");
	//auto tsize = r.getSize();
	//unsigned char* tb = (unsigned char*)malloc(tsize);
	//r.toArray(tb,tsize);
	//int size1 = 0;
	//r.fromArray(tb,&size1);


TEST(SERIALIZATION, SPEED)
{


	Stopwatch t;
	t.set_mode(REAL_TIME);
	
	auto obj_data_creation = "Custom data object creation";
	auto obj_data_serialization = "Custom data object serialization";
	auto obj_data_deserialization = "Custom data object deserialization";
	auto msg_data_creation = "Protobuf data object creation";
	auto msg_data_serialization = "Protobuf data object serialization";
	auto msg_data_deserialization = "Protobuf data object deserialization";

	auto obj_creation = "Cusom object creation";
	auto obj_serialization = "Custom object to byte array serialization";
	auto obj_deserializaion = "Cusom object instatiation from byte array";
	auto message_creation = "Protobuf message creation";
	auto message_serialization = "Protobug message serialization";
	auto message_deserialization = "Protobug message deserialization";

	for (auto epoch =0;epoch<10;epoch++){

	t.start(obj_data_creation);
	custom_response br;
	for (auto i= 0;i<5000*10;i++){
		br.m_data.insert(br.m_data.end(),"123456789 123456789");
	}
	t.stop(obj_data_creation);	

	t.start(obj_data_serialization);
	auto brsize = br.getSize();
	unsigned char* brd = (unsigned char*)malloc(brsize);
	br.toArray(brd,brsize);
	t.stop(obj_data_serialization);

	t.start(obj_data_deserialization);
	custom_response crde;
	int sizeOfDeData = 0;
	crde.fromArray(brd,&sizeOfDeData);
	t.stop(obj_data_deserialization);


	t.start(msg_data_creation);
	response respm;
	for (auto i= 0;i<5000*10;i++){
		respm.add_data("123456789 123456789");
	}
	t.stop(msg_data_creation);	

	t.start(msg_data_serialization);
	auto respms = respm.ByteSize();
	unsigned char* respmb = (unsigned char*)malloc(respms);
	respm.SerializeToArray(respmb,respms);
	t.stop(msg_data_serialization);

	t.start(msg_data_deserialization);
	response respmde;

	respmde.ParseFromArray(respmb,respms);
	t.stop(msg_data_deserialization);

	//data
	auto name = "cool data";
	auto id = "very very cool id";
	auto type = "very very cool type";
	

	////steps

    t.start(obj_creation);
	custom_request sc;
    sc.m_name = std::string(name);
	for (int i = 0;i<5000;i++){
		sc.m_ids.insert(sc.m_ids.end(),id);
	}
	for (int i = 0;i<10;i++){	
		sc.m_types.insert(sc.m_types.end(),type);
	}
	t.stop(obj_creation);


	t.start(obj_serialization);
	auto cs = sc.getSize();
	unsigned char* buffer = (unsigned char*)malloc(cs);
	sc.toArray(buffer,cs);
	t.stop(obj_serialization);


	t.start(obj_deserializaion);
	custom_request dc;
	int sizeOfDe = 0;
	dc.fromArray(buffer,&sizeOfDe);
	t.stop(obj_deserializaion);


	t.start(message_creation);
	request* s = new request();	
	s->set_name((char*)name);
	for (int i = 0;i<5000;i++){

		std::string str(id);
		s->add_ids(str);
	}
	for (int i = 0;i<10;i++){
		std::string str(type);
		s->add_types(str);
	}
	t.stop(message_creation);


	t.start(message_serialization);
	auto size = s->ByteSize();
	void* data = malloc(size);
	s->SerializeToArray(data,size);
	t.stop(message_serialization);

	
	t.start(message_deserialization);
	request* d = new request();
    d->ParseFromArray(data,size);
	t.stop(message_deserialization);
	}

	t.report(obj_data_creation);
	t.report(obj_data_serialization);
	t.report(obj_data_deserialization);
	t.report(msg_data_creation);
	t.report(msg_data_serialization);
	t.report(msg_data_deserialization);

	t.report(obj_creation);
	t.report(obj_serialization);
	t.report(obj_deserializaion);
	t.report(message_creation);
	t.report(message_serialization);
	t.report(message_deserialization);

}



int main(int argc, wchar_t* argv[])
{

	testing::InitGoogleTest(&argc,argv);
	
	RUN_ALL_TESTS();
	std::getchar();
	return 0;
}

