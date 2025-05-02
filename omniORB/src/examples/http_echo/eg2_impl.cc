// Usage: eg2_impl <endpoint options>
//
// See README for instructions.

#include <sys/stat.h>
#include <echo.hh>
#include <omniORB4/httpContext.h>

#include <iostream>
using namespace std;


class Echo_i : public POA_Echo
{
public:
  inline Echo_i() {}
  virtual ~Echo_i() {}
  virtual char* echoString(const char* mesg);
};


char* Echo_i::echoString(const char* mesg)
{
  cout << "Upcall: " << mesg << endl;
  return CORBA::string_dup(mesg);
}

//////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  omni::httpContext::certificate_authority_file = "root.pem";
  omni::httpContext::key_file                   = "server.pem";
  omni::httpContext::key_file_password          = "password";

  struct stat sb;
  if (stat(omni::httpContext::certificate_authority_file,&sb) < 0) {
    cerr << "Cannot open certificate file: "
	 << omni::httpContext::certificate_authority_file << endl;
    return 1;
  }
  if (stat(omni::httpContext::key_file,&sb) < 0) {
    cerr << "Cannot open key file: "
	 << omni::httpContext::key_file << endl;
    return 1;
  }

  try {
    CORBA::ORB_var          orb = CORBA::ORB_init(argc, argv);
    CORBA::Object_var       obj = orb->resolve_initial_references("omniINSPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    PortableServer::Servant_var<Echo_i> myecho = new Echo_i();

    // Activate the object in the INS POA with object key "echo"
    PortableServer::ObjectId_var oid =
      PortableServer::string_to_ObjectId("echo");
    
    poa->activate_object_with_id(oid, myecho);

    // Obtain a reference to the object, and print it out as a
    // stringified IOR.
    obj = myecho->_this();
    CORBA::String_var sior(orb->object_to_string(obj));
    cout << sior << endl;

    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    // Block until the ORB is shut down.
    orb->run();
  }
  catch (CORBA::SystemException& ex) {
    cerr << "Caught CORBA::" << ex._name() << endl;
  }
  catch (CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  return 0;
}
