// Usage: eg2_clt <endpoint options> <IOR or URL>
//
// See README for instructions.

#include <sys/stat.h>
#include <echo.hh>
#include <omniORB4/httpContext.h>

#include <iostream>
using namespace std;


static void hello(Echo_ptr e)
{
  CORBA::String_var src = (const char*) "Hello!";

  CORBA::String_var dest = e->echoString(src);

  cout << "I said, \"" << (char*)src << "\"." << endl
       << "The Echo object replied, \"" << (char*)dest <<"\"." << endl;
}

//////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  omni::httpContext::certificate_authority_file = "root.pem";
  omni::httpContext::key_file                   = "client.pem";
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
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    if (argc != 2) {
      cerr << "usage:  eg2_clt <object reference>" << endl;
      return 1;
    }

    CORBA::Object_var obj = orb->string_to_object(argv[1]);

    Echo_var echoref = Echo::_narrow(obj);

    if (CORBA::is_nil(echoref)) {
      cerr << "Can't narrow reference to type Echo (or it was nil)." << endl;
      return 1;
    }

    for (CORBA::ULong count=0; count<10; count++) 
      hello(echoref);

    orb->destroy();
  }
  catch (CORBA::TRANSIENT&) {
    cerr << "Caught system exception TRANSIENT -- unable to contact the "
         << "server." << endl;
  }
  catch (CORBA::SystemException& ex) {
    cerr << "Caught a CORBA::" << ex._name() << endl;
  }
  catch (CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  return 0;
}
