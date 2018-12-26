#include <iostream>
#include <set>
#include <utility>

using namespace std;

class GtpMsgKey
{
public: 
    ~GtpMsgKey() {}

    explicit GtpMsgKey(int sequenceNumber, int interfaceType, int ipEndpoint):interfaceType_(interfaceType), sequenceNumber_(sequenceNumber), ipEndpoint_(ipEndpoint) {}

    bool operator<(GtpMsgKey& rh)
    {
	    if (ipEndpoint_ < rh.getIpEndpoint())
	    {
		return true;
	    }
	    else if (ipEndpoint_ == rh.getIpEndpoint())
	    {
		if (interfaceType_ < rh.getInterfaceType())
		{
		    return true;
		}
		else if (interfaceType_ == rh.getInterfaceType())
		{
		    if (sequenceNumber_ < rh.getSequenceNumber())
		    {
			return true;
		    }
	        }
	}
    	return false;
    }

    int getInterfaceType() { return interfaceType_;}
    int getIpEndpoint() { return ipEndpoint_;}
    int getSequenceNumber() {return sequenceNumber_;}

private:

    int interfaceType_;
    int ipEndpoint_;
    int sequenceNumber_;
};


class PendingReq
{
public:

	PendingReq(GtpMsgKey& k):key(k) {}

	GtpMsgKey key;
	GtpMsgKey& getKey() {return key;}
};


class PendingReqSorter : public std::binary_function<PendingReq*, PendingReq*, bool>
{
public: 
	bool operator()(PendingReq* lh,PendingReq* rh)
	{
		return lh->getKey() < rh->getKey();
	}
};

typedef std::set<PendingReq*, PendingReqSorter> PendingReqSet;

typedef std::pair<PendingReqSet::iterator, bool> InsertPair;

int main()
{
/*
	GtpMsgKey key1(12, 5, 10);
	GtpMsgKey key2(11, 5, 10);

	PendingReqSet reqSet;

	PendingReq req1(key1);
	PendingReq req2(key2);

	InsertPair res = reqSet.insert(&req1);
	if (res.second)
	{
		cout << "insert success" << endl;
	}
	
	res = reqSet.insert(&req2);
	if (res.second)
	{
		cout << "insert success" << endl;
	}
	


	GtpMsgKey key1(12, 5, 10);
	GtpMsgKey key2(12, 5, 10);


	if (key1 < key2)
	{
		cout << "key1 < key2" << endl;
	}
	else
	{
		cout << " key1 not < key2" << endl;
	}
*/

	set<int> ids;
	std::pair<set<int>::iterator, bool> pa;
	pa = ids.insert(1);
	pa = ids.insert(2);
	pa = ids.insert(3);
	pa = ids.insert(4);
	if (pa.second)
	{
		cout << "good" << endl;
	}
	else
	{
		cout << "bad" << endl;
	}

  for (auto i : ids)
  {
      cout << i << endl;
  }
}
