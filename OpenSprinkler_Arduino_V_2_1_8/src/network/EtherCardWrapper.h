/* ==========================================================================================================
This is a fork of Rays OpenSprinkler code thats amended to use alternative hardware:

EtherCardW5100.h and EtherCardW5100.cpp implements a minimal set of functions
as a wrapper to replace the ENC28J60 EtherCard class libraries with the standard
Arduino Wiznet5100 Ethernet library.

Version:     Opensprinkler 2.1.8

Date:        May 2018

Repository:  https://github.com/plainolddave/OpenSprinkler-Arduino

License:     Creative Commons Attribution-ShareAlike 3.0 license

Refer to the README file for more information

========================================================================================================== */

#ifndef _ETHERCARD_WRAPPER_h_
#define _ETHERCARD_WRAPPER_h_

#include <stdarg.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <assert.h>

// =================================================================
//-- Property.hpp --
// This class try to simulate property for C++, using template technique.
// https://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4031/Implementing-a-Property-in-C.htm
// =================================================================

#define READ_ONLY 1
#define WRITE_ONLY 2
#define READ_WRITE 3

template<typename Container, typename ValueType, int nPropType>
class property
{
public:
    property()
    {
        m_cObject = NULL;
        Set = NULL;
        Get = NULL;
    }
    //-- This to set a pointer to the class that contain the property --
    void setContainer(Container* cObject)
    {
        m_cObject = cObject;
    }
    //-- Set the set member function that will change the value --
    void setter(void (Container::*pSet)(ValueType value))
    {
        if ((nPropType == WRITE_ONLY) || (nPropType == READ_WRITE))
            Set = pSet;
        else
            Set = NULL;
    }
    //-- Set the get member function that will retrieve the value --
    void getter(ValueType(Container::*pGet)())
    {
        if ((nPropType == READ_ONLY) || (nPropType == READ_WRITE))
            Get = pGet;
        else
            Get = NULL;
    }
    //-- Overload the '=' sign to set the value using the set member --
    ValueType operator =(const ValueType& value)
    {
        assert(m_cObject != NULL);
        assert(Set != NULL);
        (m_cObject->*Set)(value);
        return value;
    }

    //-- To make possible to cast the property class to the internal type --
    operator ValueType()
    {
        assert(m_cObject != NULL);
        assert(Get != NULL);
        return (m_cObject->*Get)();
    }

private:
    Container * m_cObject;//-- Pointer to the module that contain the property --
    void (Container::*Set)(ValueType value);//-- Pointer to set member function --
    ValueType(Container::*Get)();//-- Pointer to get member function --
};

// =================================================================
// Ethercard wrapper 
// =================================================================

template <class T> class EtherCardWrapper
{
protected:
    T e;
public:
    uint8_t *mymac;                 // MAC address
    uint8_t *myip;                  // IP address
    uint8_t *netmask;               // Netmask
    uint8_t *broadcastip;           // Subnet broadcast address
    uint8_t *gwip;                  // Gateway
    uint8_t *dhcpip;                // DHCP server IP address
    uint8_t *dnsip;                 // DNS server IP address
    uint8_t *hisip;                 // DNS lookup result

    inline EtherCardWrapper()
    {
        gwip = e.gwip;
        mymac = e.mymac;
        myip = e.myip;
        netmask = e.netmask;
        broadcastip = e.broadcastip;
        gwip = e.gwip;
        dhcpip = e.dhcpip;
        dnsip = e.dnsip;
        hisip = e.hisip;
        buffer = e.buffer;

        hisport.setContainer(this);
        hisport.getter(&EtherCardWrapper::get_hisport);
        hisport.setter(&EtherCardWrapper::set_hisport);

        using_dhcp.setContainer(this);
        using_dhcp.getter(&EtherCardWrapper::get_using_dhcp);
        using_dhcp.setter(&EtherCardWrapper::set_using_dhcp);

        persist_tcp_connection.setContainer(this);
        persist_tcp_connection.getter(&EtherCardWrapper::get_persist_tcp_connection);
        persist_tcp_connection.setter(&EtherCardWrapper::set_persist_tcp_connection);

        delaycnt.setContainer(this);
        delaycnt.getter(&EtherCardWrapper::get_delaycnt);
        delaycnt.setter(&EtherCardWrapper::set_delaycnt);
    };

    // TCP port to connect to (default 80)
    uint16_t get_hisport() { return e.hisport; }
    void set_hisport(uint16_t value) { e.hisport = value; }
    property<EtherCardWrapper, uint16_t, READ_WRITE> hisport; 

    // True if using DHCP
    bool get_using_dhcp() { return e.using_dhcp; }
    void set_using_dhcp(bool value) { e.using_dhcp = value; }
    property<EtherCardWrapper, bool, READ_WRITE> using_dhcp;

    // False to break connections on first packet received
    bool get_persist_tcp_connection() { return e.persist_tcp_connection; }
    void set_persist_tcp_connection(bool value) { e.persist_tcp_connection = value; }
    property<EtherCardWrapper, bool, READ_WRITE> persist_tcp_connection;

    // Counts number of cycles of packetLoop when no packet recieved - used to trigger periodic gateway ARP request
    uint16_t get_delaycnt() { return e.delaycnt; }
    void set_delaycnt(uint16_t value) { e.delaycnt = value; }
    property<EtherCardWrapper, uint16_t, READ_WRITE> delaycnt;

    // EtherCard.cpp
    /**   @brief  Initialise the network interface
    *     @param  size Size of data buffer
    *     @param  macaddr Hardware address to assign to the network interface (6 bytes)
    *     @param  csPin Arduino pin number connected to chip select. Default = 8
    *     @return <i>uint8_t</i> Firmware version or zero on failure.
    */
    inline uint8_t begin(
        const uint16_t size,
        const uint8_t* macaddr,
        uint8_t csPin = 8)
    {
        return e.begin(size, macaddr, csPin);
    };

    /**   @brief  Configure network interface with static IP
    *     @param  my_ip IP address (4 bytes). 0 for no change.
    *     @param  gw_ip Gateway address (4 bytes). 0 for no change. Default = 0
    *     @param  dns_ip DNS address (4 bytes). 0 for no change. Default = 0
    *     @param  mask Subnet mask (4 bytes). 0 for no change. Default = 0
    *     @return <i>bool</i> Returns true on success - actually always true
    */
    inline bool staticSetup(
        const uint8_t* my_ip,
        const uint8_t* gw_ip = 0,
        const uint8_t* dns_ip = 0,
        const uint8_t* mask = 0)
    {
        return e.staticSetup(my_ip, gw_ip, dns_ip, mask);
    };

    //// tcpip.cpp
    ///**   @brief  Sends a UDP packet to the IP address of last processed recieved packet
    //*     @param  data Pointer to data payload
    //*     @param  len Size of data payload (max 220)
    //*     @param  port Destination IP port
    //*/
    //inline void makeUdpReply(char *data, uint8_t len, uint16_t port);

    /**   @brief  Parse recieved data
    *     @param  plen Size of data to parse (e.g. return value of packetRecieve()).
    *     @return <i>uint16_t</i> Offset of TCP payload data in data buffer or zero if packet processed
    *     @note   Data buffer is shared by recieve and transmit functions
    *     @note   Only handles ARP and IP
    */
    inline uint16_t packetLoop(uint16_t plen)
    {
        return e.packetLoop(plen);
    }

    ///**   @brief  Accept a TCP/IP connection
    //*     @param  port IP port to accept on - do nothing if wrong port
    //*     @param  plen Number of bytes in packet
    //*     @return <i>uint16_t</i> Offset within packet of TCP payload. Zero for no data.
    //*/
    //inline uint16_t accept(uint16_t port, uint16_t plen);

    ///**   @brief  Send a respons to a HTTP request
    //*     @param  dlen Size of the HTTP (TCP) payload
    //*/
    //inline void httpServerReply(uint16_t dlen);

    /**   @brief  Send a response to a HTTP request
    *     @param  dlen Size of the HTTP (TCP) payload
    *     @param  flags TCP flags
    */
    inline void httpServerReply_with_flags(uint16_t dlen, uint8_t flags)
    {
        e.httpServerReply_with_flags(dlen, flags);
    }

    /**   @brief  Acknowledge TCP message
    *     @todo   Is this / should this be private?
    */
    inline void httpServerReplyAck()
    {
        e.httpServerReplyAck();
    };

    ///**   @brief  Set the gateway address
    //*     @param  gwipaddr Gateway address (4 bytes)
    //*/
    //inline void setGwIp(const uint8_t *gwipaddr);

    ///**   @brief  Updates the broadcast address based on current IP address and subnet mask
    //*/
    //inline void updateBroadcastAddress();

    ///**   @brief  Check if got gateway hardware address (ARP lookup)
    //*     @return <i>unit8_t</i> True if gateway found
    //*/
    //inline uint8_t clientWaitingGw();

    ///**   @brief  Prepare a TCP request
    //*     @param  result_cb Pointer to callback function that handles TCP result
    //*     @param  datafill_cb Pointer to callback function that handles TCP data payload
    //*     @param  port Remote TCP/IP port to connect to
    //*     @return <i>unit8_t</i> ID of TCP/IP session (0-7)
    //*     @note   Return value provides id of the request to allow up to 7 concurrent requests
    //*/
    //inline uint8_t clientTcpReq(uint8_t(*result_cb)(uint8_t, uint8_t, uint16_t, uint16_t),
    //    uint16_t(*datafill_cb)(uint8_t), uint16_t port);

    ///**   @brief  Prepare HTTP request
    //*     @param  urlbuf Pointer to c-string URL folder
    //*     @param  urlbuf_varpart Pointer to c-string URL file
    //*     @param  hoststr Pointer to c-string hostname
    //*     @param  additionalheaderline Pointer to c-string with additional HTTP header info
    //*     @param  callback Pointer to callback function to handle response
    //*     @note   Request sent in main packetloop
    //*/
    //inline void browseUrl(const char *urlbuf, const char *urlbuf_varpart,
    //    const char *hoststr, const char *additionalheaderline,
    //    void(*callback)(uint8_t, uint16_t, uint16_t));

    /**   @brief  Prepare HTTP request
    *     @param  urlbuf Pointer to c-string URL folder
    *     @param  urlbuf_varpart Pointer to c-string URL file
    *     @param  hoststr Pointer to c-string hostname
    *     @param  callback Pointer to callback function to handle response
    *     @note   Request sent in main packetloop
    */
    inline void browseUrl(
        const char *urlbuf,
        const char *urlbuf_varpart,
        const char *hoststr,
        void(*callback)(uint8_t, uint16_t, uint16_t))
    {
        e.browseUrl(urlbuf, urlbuf_varpart, hoststr, callback);
    };

    /** Ray: modified browseUrl, allows hoststr to be defined as RAM string */
    inline void browseUrlRamHost(
        const char *urlbuf,
        const char *urlbuf_varpart,
        const char *hoststr,
        void(*callback)(uint8_t, uint16_t, uint16_t))
    {
        e.browseUrlRamHost(urlbuf, urlbuf_varpart, hoststr, callback);
    };

    //inline void browseUrlRamHost(const char *urlbuf, const char *urlbuf_varpart,
    //    const char *hoststr, const char *additionalheaderline,
    //    void(*callback)(uint8_t, uint16_t, uint16_t));

    ///**   @brief  Prepare HTTP post message
    //*     @param  urlbuf Pointer to c-string URL folder
    //*     @param  hoststr Pointer to c-string hostname
    //*     @param  additionalheaderline Pointer to c-string with additional HTTP header info
    //*     @param  postval Pointer to c-string HTML Post value
    //*     @param  callback Pointer to callback function to handle response
    //*     @note   Request sent in main packetloop
    //*/
    inline void httpPost(const char *urlbuf, const char *hoststr,
        const char *additionalheaderline, const char *postval,
        void(*callback)(uint8_t, uint16_t, uint16_t)) {};

    inline void httpPostVar(const char *urlbuf, const char *hoststr,
        const char *urlbuf_varpart, const char *postval,
        void(*callback)(uint8_t, uint16_t, uint16_t)) {};

    /**   @brief  Send   request
    *     @param  ntpip IP address of NTP server
    *     @param  srcport IP port to send from
    */
    inline void ntpRequest(uint8_t *ntpip, uint8_t srcport)
    {
        e.ntpRequest(ntpip, srcport);
    };

    /**   @brief  Process network time protocol response
    *     @param  time Pointer to integer to hold result
    *     @param  dstport_l Destination port to expect response. Set to zero to accept on any port
    *     @return <i>uint8_t</i> True (1) on success
    */
    inline uint8_t ntpProcessAnswer(uint32_t *time, uint8_t dstport_l)
    {
        return e.ntpProcessAnswer(time, dstport_l);
    };

    ///**   @brief  Prepare a UDP message for transmission
    //*     @param  sport Source port
    //*     @param  dip Pointer to 4 byte destination IP address
    //*     @param  dport Destination port
    //*/
    //inline void udpPrepare(uint16_t sport, const uint8_t *dip, uint16_t dport);

    ///**   @brief  Transmit UDP packet
    //*     @param  len Size of payload
    //*/
    //inline void udpTransmit(uint16_t len);

    ///**   @brief  Sends a UDP packet
    //*     @param  data Pointer to data
    //*     @param  len Size of payload (maximum 220 octets / bytes)
    //*     @param  sport Source port
    //*     @param  dip Pointer to 4 byte destination IP address
    //*     @param  dport Destination port
    //*/
    //inline void sendUdp(const char *data, uint8_t len, uint16_t sport,
    //    const uint8_t *dip, uint16_t dport);

    ///**   @brief  Resister the function to handle ping events
    //*     @param  cb Pointer to function
    //*/
    //inline void registerPingCallback(void(*cb)(uint8_t*));

    /**   @brief  Send ping
    *     @param  destip Ponter to 4 byte destination IP address
    */
    inline void clientIcmpRequest(const uint8_t *destip)
    {
        e.clientIcmpRequest(destip);
    };

    /**   @brief  Check for ping response
    *     @param  ip_monitoredhost Pointer to 4 byte IP address of host to check
    *     @return <i>uint8_t</i> True (1) if ping response from specified host
    */
    inline uint8_t packetLoopIcmpCheckReply(const uint8_t *ip_monitoredhost)
    {
        return e.packetLoopIcmpCheckReply(ip_monitoredhost);
    };

    ///**   @brief  Send a wake on lan message
    //*     @param  wolmac Pointer to 6 byte hardware (MAC) address of host to send message to
    //*/
    //inline void sendWol(uint8_t *wolmac);

    //// new stash-based API
    ///**   @brief  Send TCP request
    //*/
    //inline uint8_t tcpSend();

    ///**   @brief  Get TCP reply
    //*     @return <i>char*</i> Pointer to TCP reply payload. NULL if no data.
    //*/
    //inline const char* tcpReply(uint8_t fd);

    ///**   @brief  Configure TCP connections to be persistent or not
    //*     @param  persist True to maintain TCP connection. False to finish TCP connection after first packet.
    //*/
    //inline void persistTcpConnection(bool persist);

    ////udpserver.cpp
    ///**   @brief  Register function to handle incomint UDP events
    //*     @param  callback Function to handle event
    //*     @param  port Port to listen on
    //*/
    //inline void udpServerListenOnPort(UdpServerCallback callback, uint16_t port);

    ///**   @brief  Pause listing on UDP port
    //*     @brief  port Port to pause
    //*/
    //inline void udpServerPauseListenOnPort(uint16_t port);

    ///**   @brief  Resume listing on UDP port
    //*     @brief  port Port to pause
    //*/
    //inline void udpServerResumeListenOnPort(uint16_t port);

    ///**   @brief  Check if UDP server is listening on any ports
    //*     @return <i>bool</i> True if listening on any ports
    //*/
    //inline bool udpServerListening();                        //called by tcpip, in packetLoop

    ///**   @brief  Passes packet to UDP Server
    //*     @param  len Not used
    //*     @return <i>bool</i> True if packet processed
    //*/
    //inline bool udpServerHasProcessedPacket(uint16_t len);    //called by tcpip, in packetLoop

    //// dhcp.cpp
    ///**   @brief  Update DHCP state
    //*     @param  len Length of recieved data packet
    //*/
    //inline void DhcpStateMachine(uint16_t len);

    ///**   @brief Not implemented
    //*     @todo Implement dhcpStartTime or remove declaration
    //*/
    //inline uint32_t dhcpStartTime();

    ///**   @brief Not implemented
    //*     @todo Implement dhcpLeaseTime or remove declaration
    //*/
    //inline uint32_t dhcpLeaseTime();

    ///**   @brief Not implemented
    //*     @todo Implement dhcpLease or remove declaration
    //*/
    //inline bool dhcpLease();

    /**   @brief  Configure network interface with DHCP
    *     @return <i>bool</i> True if DHCP successful
    *     @note   Blocks until DHCP complete or timeout after 60 seconds
    */
    inline bool dhcpSetup()
    {
        return e.dhcpSetup();
    };

    ///**   @brief  Register a callback for a specific DHCP option number
    //*     @param  <i>option</i> The option number to request from the DHCP server
    //*     @param  <i>callback</i> The function to be call when the option is received
    //*/
    //inline void dhcpAddOptionCallback(uint8_t option, DhcpOptionCallback callback);

    // dns.cpp
    /**   @brief  Perform DNS lookup
    *     @param  name Host name to lookup
    *     @param  fromRam Set true to look up cached name. Default = false
    *     @return <i>bool</i> True on success.
    *     @note   Result is stored in <i>hisip</i> member
    */
    inline bool dnsLookup(const char* name, bool fromRam = false)
    {
        return e.dnsLookup(name, fromRam);
    };

    //// webutil.cpp
    ///**   @brief  Copies an IP address
    //*     @param  dst Pointer to the 4 byte destination
    //*     @param  src Pointer to the 4 byte source
    //*     @note   There is no check of source or destination size. Ensure both are 4 bytes
    //*/
    //inline void copyIp(uint8_t *dst, const uint8_t *src);

    ///**   @brief  Copies a hardware address
    //*     @param  dst Pointer to the 6 byte destination
    //*     @param  src Pointer to the 6 byte destination
    //*     @note   There is no check of source or destination size. Ensure both are 6 bytes
    //*/
    //inline void copyMac(uint8_t *dst, const uint8_t *src);

    /**   @brief  Output to serial port in dotted decimal IP format
    *     @param  buf Pointer to 4 byte IP address
    *     @note   There is no check of source or destination size. Ensure both are 4 bytes
    */
    inline void printIp(const uint8_t *buf)
    {
        e.printIp(buf);
    };

    /**   @brief  Output message and IP address to serial port in dotted decimal IP format
    *     @param  msg Pointer to null terminated string
    *     @param  buf Pointer to 4 byte IP address
    *     @note   There is no check of source or destination size. Ensure both are 4 bytes
    */
    inline void printIp(const char* msg, const uint8_t *buf)
    {
        e.printIp(msg, buf);
    };

    /**   @brief  Output Flash String Helper and IP address to serial port in dotted decimal IP format
    *     @param  ifsh Pointer to Flash String Helper
    *     @param  buf Pointer to 4 byte IP address
    *     @note   There is no check of source or destination size. Ensure both are 4 bytes
    *     @todo   What is a FlashStringHelper?
    */
    inline void printIp(const __FlashStringHelper *ifsh, const uint8_t *buf)
    {
        e.printIp(ifsh, buf);
    };

    ///**   @brief  Search for a string of the form key=value in a string that looks like q?xyz=abc&uvw=defgh HTTP/1.1\\r\\n
    //*     @param  str Pointer to the null terminated string to search
    //*     @param  strbuf Pointer to buffer to hold null terminated result string
    //*     @param  maxlen Maximum length of result
    //*     @param  key Pointer to null terminated string holding the key to search for
    //*     @return <i>unit_t</i> Length of the value. 0 if not found
    //*     @note   Ensure strbuf has memory allocated of at least maxlen + 1 (to accomodate result plus terminating null)
    //*/
    //// ray: modified to add support for key stored in pgm memory
    //inline uint8_t findKeyVal(const char *str, char *strbuf,
    //    uint8_t maxlen, const char *key, bool key_in_pgm = false,
    //    uint8_t *keyfound = NULL);

    ///**   @brief  Decode a URL string e.g "hello%20joe" or "hello+joe" becomes "hello joe"
    //*     @param  urlbuf Pointer to the null terminated URL
    //*     @note   urlbuf is modified
    //*/
    //inline void urlDecode(char *urlbuf);

    ///**   @brief  Encode a URL, replacing illegal charaters like ' '
    //*     @param  str Pointer to the null terminated string to encode
    //*     @param  urlbuf Pointer to a buffer to contain the null terminated encoded URL
    //*     @note   There must be enough space in urlbuf. In the worst case that is 3 times the length of str
    //*/
    //inline  void urlEncode(char *str, char *urlbuf);

    ///**   @brief  Convert an IP address from dotted decimal formated string to 4 bytes
    //*     @param  bytestr Pointer to the 4 byte array to store IP address
    //*     @param  str Pointer to string to parse
    //*     @return <i>uint8_t</i> 0 on success
    //*/
    //inline uint8_t parseIp(uint8_t *bytestr, char *str);

    ///**   @brief  Convert a byte array to a human readable display string
    //*     @param  resultstr Pointer to a buffer to hold the resulting null terminated string
    //*     @param  bytestr Pointer to the byte array containing the address to convert
    //*     @param  len Length of the array (4 for IP address, 6 for hardware (MAC) address)
    //*     @param  separator Delimiter character (typically '.' for IP address and ':' for hardware (MAC) address)
    //*     @param  base Base for numerical representation (typically 10 for IP address and 16 for hardware (MAC) address
    //*/
    //inline void makeNetStr(char *resultstr, uint8_t *bytestr, uint8_t len,
    //    char separator, uint8_t base);

    // =================================================================
    // ENC28J60.cpp 
    // =================================================================

    // Data buffer (shared by recieve and transmit)
    uint8_t *buffer; 

    //static uint16_t bufferSize; //!< Size of data buffer
    //static bool broadcast_enabled; //!< True if broadcasts enabled (used to allow temporary disable of broadcast for DHCP or other internal functions)

    //!< Pointer to the start of TCP payload
    inline uint8_t* tcpOffset()
    {
        return e.tcpOffset();
    }

    ///**   @brief  Initialise SPI interface
    //*     @note   Configures Arduino pins as input / output, etc.
    //*/
    //static void initSPI();

    ///**   @brief  Initialise network interface
    //*     @param  size Size of data buffer
    //*     @param  macaddr Pointer to 4 byte hardware (MAC) address
    //*     @param  csPin Arduino pin used for chip select (enable network interface SPI bus). Default = 8
    //*     @return <i>uint8_t</i> ENC28J60 firmware version or zero on failure.
    //*/
    //static uint8_t initialize(const uint16_t size, const uint8_t* macaddr,
    //    uint8_t csPin = 8);

    ///**   @brief  Check if network link is connected
    //*     @return <i>bool</i> True if link is up
    //*/
    //static bool isLinkUp();

    ///**   @brief  Sends data to network interface
    //*     @param  len Size of data to send
    //*     @note   Data buffer is shared by recieve and transmit functions
    //*/
    //static void packetSend(uint16_t len);

    /**   @brief  Copy recieved packets to data buffer
    *     @return <i>uint16_t</i> Size of recieved data
    *     @note   Data buffer is shared by recieve and transmit functions
    */
    inline uint16_t packetReceive()
    {
        return e.packetReceive();
    }

    ///**   @brief  Copy data from ENC28J60 memory
    //*     @param  page Data page of memory
    //*     @param  data Pointer to buffer to copy data to
    //*/
    //static void copyout(uint8_t page, const uint8_t* data);

    ///**   @brief  Copy data to ENC28J60 memory
    //*     @param  page Data page of memory
    //*     @param  data Pointer to buffer to copy data from
    //*/
    //static void copyin(uint8_t page, uint8_t* data);

    ///**   @brief  Get single byte of data from ENC28J60 memory
    //*     @param  page Data page of memory
    //*     @param  off Offset of data within page
    //*     @return Data value
    //*/
    //static uint8_t peekin(uint8_t page, uint8_t off);

    ///**   @brief  Put ENC28J60 in sleep mode
    //*/
    //static void powerDown();  // contrib by Alex M.

    ///**   @brief  Wake ENC28J60 from sleep mode
    //*/
    //static void powerUp();    // contrib by Alex M.

    ///**   @brief  Enable reception of broadcast messages
    //*     @param  temporary Set true to temporarily enable broadcast
    //*     @note   This will increase load on recieved data handling
    //*/
    //static void enableBroadcast(bool temporary = false);

    ///**   @brief  Disable reception of broadcast messages
    //*     @param  temporary Set true to only disable if temporarily enabled
    //*     @note   This will reduce load on recieved data handling
    //*/
    //static void disableBroadcast(bool temporary = false);

    ///**   @brief  Enables reception of mulitcast messages
    //*     @note   This will increase load on recieved data handling
    //*/
    //static void enableMulticast();

    ///**   @brief  Disable reception of mulitcast messages
    //*     @note   This will reduce load on recieved data handling
    //*/
    //static void disableMulticast();

    ///**   @brief  Reset and fully initialise ENC28J60
    //*     @param  csPin Arduino pin used for chip select (enable SPI bus)
    //*     @return <i>uint8_t</i> 0 on failure
    //*/
    //static uint8_t doBIST(uint8_t csPin = 8);

    // =================================================================
    // Additional help functions
    // =================================================================

    inline void printMac(const __FlashStringHelper *msg, const char *buf)
    {
        Serial.print(msg);
        this->printMac(buf);
        Serial.println();
    }

    inline void printMac(const char* msg, const uint8_t *buf)
    {
        Serial.print(msg);
        this->printMac(buf);
        Serial.println();
    }

    inline void printMac(const __FlashStringHelper *msg, const uint8_t *buf)
    {
        Serial.print(msg);
        this->printMac(buf);
        Serial.println();
    }

    inline void printMac(const uint8_t *buf)
    {
        for (uint8_t i = 0; i < 6; ++i) 
        {
            Serial.print(buf[i], HEX);
            if (i < 5)
                Serial.print(':');
        }
    }
};

#endif
