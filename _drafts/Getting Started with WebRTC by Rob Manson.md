important to understand that WebRTC is not really a single technology, but more a collection of standards and protocols,

new XHR API enabled web developers to create web applications that didn't need to navigate to a new page to update their content or user interface. It allowed them to utilize server-based web services that provided access to structured data and snippets of pages or other content.

enables individual web browsers to stream data directly to each other without the need for sending it via intermediary servers. This new form of peer-to-peer communication is built upon a new set of APIs that is being standardized by the Web Real-Time Communications Working Group

This enables two or more WebRTC capable devices or peers to find each other, exchange contact details, negotiate a session that defines how they will communicate, and then finally establish the direct peer-to-peer streams of media that flows between them.

Connect users
• Start signals
• Find candidates
• Negotiate media sessions
• Start RTCPeerConnection streams

This type of web page, often, assigns a unique token that can be used to link the communication between these two browsers.

In this context, "signaling messages" are simply any form of communication that helps these two browsers establish and control their WebRTC communication. The WebRTC standards don't define exactly how

The next step is for the two browsers to exchange information about their networks, and how they can be contacted. This process is commonly described as "finding candidates", and at the end each browser should be mapped to a directly accessible network interface and port.

Interactive Connectivity Establishment (ICE) framework (http://en.wikipedia.org/wiki/Interactive_Connectivity_Establishment) that handles connecting to a STUN server and then falling back to a TURN server where required.

type and format of media (for example, audio and video) they will exchange including codec, resolution, bitrate, and so on. This is usually negotiated using an offer/answer based model, built upon the Session Description Protocol (SDP) (http://en.wikipedia.org/wiki/Session_Description_Protocol). This has been defined as the JavaScript Session Establishment Protocol (JSEP);