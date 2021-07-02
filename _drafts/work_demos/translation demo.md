```mermaid
graph LR
id1[User]
id2[Agent]
id3[Agents-service]
id4[Translation-service]
id5[Controller]
id6[Data-service]

subgraph message_sending_section
direction LR
id1-->|send user msg|id5
id5-->|send translated user msg|id2
end

subgraph processing
direction TB
id5-->|translate user msg|id4
id4-->|return translated user msg|id5
id4-->|send translated agent msg|id3
id3-->|agent msg to translate|id4
id3-->id5
id2-->id3
id3-->id6
id6-->id3
end

```

![[./media/Screenshot 2021-07-02 at 11.51.34.png]]
feature list
1. normal assignment with translation
2. autodetect
3. per message translation
4. transfer
5. previous messages translate (on lang change, on transfer)