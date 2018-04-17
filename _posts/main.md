---
# 19.
title: *From*: "Modeling: A Study in Words and Meanings" by Willard McCarthy
subtitle:
author;
date: \today
bibliography: biblio.bib
cms-fullnote.csl

## Willard McCarty

>> Out on site, you were never parted from your plans. They were your Bible. They got dog-eared, yellowed, smeared with mud, peppered with little holes from where you had unrolled them on the ground. But although so sacred, the plans were only the start. Once you got out there on the site everything was different. No matter how carefully done, the plans could not foresee the variables. It was always interesting, this moment when you saw for the first time the actual site rather than the idealised drawings of it.


>> -He knew men who hated the variables. They had their plans and by golly they were going to stick to them. If the site did not match the drawings it was like a personal insult.

>> He himself liked the variables best. He liked the way that the solution to one problem created another problem further down the line, so that you had to think up something else, and that in turn created another problem to solve. It was an exchange, backwards and forwards. Some men thought of it as a war, but to him it was more like a conversation.

>> Kate Grenville, The Idea of Perfection (Sydney: Picador, 1999): 62–3

# Introduction

The question of modeling arises naturally for humanities computing from the prior question of what its practitioners across the disciplines have in common. What are they all doing with their computers that we might find in their diverse activities indications of a coherent or cohesible practice? How do we make the best, most productive sense of what we observe? There are, of course, many answers: practice varies from person to person, from project to project, and ways of construing it perhaps vary even more. In this chapter I argue for modeling as a model of such a practice. I have three confluent goals: to identify humanities computing with an intellectual ground shared by the older disciplines, so that we may say how and to what extent our field is of as well as in the humanities, how it draws from and adds to them; at the same time to reflect experience with computers "in the wild"; and to aim at the most challenging problems, and so the most intellectually rewarding future now imaginable.

 My primary concern here is, as Confucius almost said, that we use the correct word for the activity we share lest our practice go awry for want of understanding (Analects 13.3). Several words are on offer. By what might be called a moral philology I examine them, arguing for the most popular of these, "modeling." The nominal form, "model", is of course very useful and even more popular, but for reasons I will adduce, its primary virtue is that properly defined it defaults to the present participle, its semantic lemma. Before getting to the philology I discuss modeling in the light of the available literature and then consider the strong and learned complaints about the term.

# Background

Let me begin with provisional definitions[^1]. By "modeling" I mean the heuristic process of constructing and manipulating models', a "model" I take to be either a representation of something for purposes of study, or a design for realizing something new. These two senses follow Clifford Geertz's analytic distinction between a denotative "model of" such as a grammar describing the features of a language, and an exemplary "model for" such as an architectural plan [(@Geertz 1973: 93)][^2]. In both cases, as the literature consistently emphasizes, a model is by nature a simplified and therefore fictional or idealized representation, often taking quite a rough-and-ready form: hence the term "tinker toy" model from physics, accurately suggesting play, relative crudity, and heuristic purpose ([@Cartwright 1983]: 158). By nature modeling defines a ternary relationship in which it mediates epistemologically, between modeler and modeled, researcher and data or theory and the world ([@Morrison and Morgan] 1999). Since modeling is fundamentally relational, the same object may in different contexts play either role: thus, e.g., the grammar may function prescriptively, as a model for correct usage, the architectural plan descriptively, as a model of an existing style. The distinction also reaches its vanishing point in the convergent purposes of modeling: the model of exists to tell us that we do not know, the model for to give us what we do not yet have. Models *realize*.

Perhaps the first question to ask is what such a process has to do with computing, since as the examples suggest neither of the two senses of "model" assumes it unless the definition is further qualified. In history, for example, Gordon Leff has argued that models have always been implicit in scholarly practice [@(Leff 1972)]. Leff cites, e.g., the historic-graphical notion of "epoch", but any well-articulated idea would qualify as a model of its subject. Nevertheless, Leff notes that as M. I. Finley said in Ancient History: Evidence and Models, "model-construction is rare among all but economic historians"; Finley recommends Max Weber's parallel concept of "ideal types", which "expresses clearly the nature and function of models in historical inquiry" (1986: 60f). Explicit model-construction is still rare in mainstream humanities scholarship. Even for non-computational research in the social sciences, it is more common, as Finley's demarcation suggests. For example, political schemes by nature model for a better or at least different world, even if like Marx's historiography they begin as models of it; delineating them as models is the scholar's obvious work [@(Mironesco 2002)]. Nevertheless, outside computationally affected scholarly practice Marvin Minsky's simple, straightforward definition remains alien in style and in thought: "To an observer B, an object A* is a model of an object A to the extent that B can use A* to answer questions that interest him about A" [(@Minsky 1995)].

A strong temptation for us here is to dismiss the residual alienness of Minsky's formulation and to accept, as we have accepted computing, the reified, explicit "model" of Minsky's definition as what we really have been doing all along. This would, however, be a serious error. As with the relationship of hypertext to earlier ways of referring [(@McCarty 2002)], the new form of expression, with its vocabulary and tools, means an altered way of thinking. A historical imagination is required to see what this means.

Two effects of computing make the distinction between "idea" or other sort of mental construct on the one hand, and on the other "model" in the sense we require: first, the demand for computational tractability, i.e., for complete explicitness and absolute consistency; second, the manipulability that a computational representation provides.

The first effects a sea-change by forcing us to confront the radical difference between what we know and what we can specify computationally, leading to the epistemological question of *how we know what we know.* On the one hand, as Michael Polanyi observed, "we can know more than we can tell" (1966: 4–5). Computational form, which accepts only that which can be told explicitly and precisely, is thus radically inadequate for representing the full range of knowledge – hence useful for isolating the tacit or inchoate kinds. On the other hand, we need to trust what we somehow know, at least provisionally, in order not to lose all that goes without saying or cannot be said in computational form.

Take, for example, knowledge one might have of a particular thematic concentration in a deeply familiar work of literature. In modeling one begins by privileging this knowledge, however wrong it might later turn out to be, then building a computational representation of it, e.g., by specifying a structured vocabulary of word-forms in a text-analysis tool. In the initial stages of use, this model would be almost certain to reveal trivial errors of omission and commission. Gradually, however, through perfective iteration trivial error is replaced by meaningful surprise. There are in general two ways in which a model may violate expectations and so surprise us: either by a success we cannot explain, e.g., finding an occurrence where it should not be; or by a likewise inexplicable failure, e.g., not finding one where it is otherwise clearly present. In both cases modeling problematizes. As a tool of research, then, modeling succeeds intellectually when it results in failure, either directly within the model itself or indirectly through ideas it shows to be inadequate. This failure, in the sense of expectations violated, is, as we will see, fundamental to modeling.

The second quality of "model" that distinguishes it from "idea" is manipulability, i.e., the capability of being handled, managed, worked, or treated by manual and, by extension, any mechanical means (OED: la.). Change is common to both models and ideas, but at greater or lesser metaphorical distance, "model" denotes a concrete, articulated plan inviting the etymological sense of action-by-hand (L. manus) in response. Manipulation in turn requires something that can be handled (physical objects, diagrams, or symbols of a formal language) – and a time-frame sufficiently brief that the emphasis falls on the process rather than its product. In other words, the modeling system must be interactive. Manipulable objects from the physical to the metaphorical have characterized mathematics, engineering, the physical sciences, and the arts ab wo, but with exceptions the necessary time-frame, allowing for interactivity, has been possible only with computing. With its advent, Minsky has noted, models could be "conceived, tested, and discarded in days or weeks instead of years" (1991). Computing met research easily in fields where modeling was already an explicit method because, Brian Cantwell Smith has pointed out, models are fundamental to computing: to do anything useful at all a computer must have a model of something, real or imaginary, in software. But in the context of computing, models per se are not the point. What distinguishes computers from other kinds of machines, Smith notes, is that "they run by manipulating representations, and representations are always formulated in terms of models" [(@Smith 1995/1985:] 460; cf. [@Fetzer 1999]: 23).

In other words, computational models, however finely perfected, are better understood as *temporary states in a process of coming to know* rather than fixed structures of knowledge. It is of course possible to argue ideologically, as some still do, that we are converging on and will achieve such structures,[^3] but in any case these structures would not then be *models* and would no longer have reason to exist in software. (Note that the history of computing is the story of ever more complex and extensive software, not less, despite the fact that implementations in hardware are faster and can be cheaper.) For the moment and the foreseeable future, then, *computers are essentially modeling machines, not knowledge jukeboxes*. To think of them as the latter is profoundly to misunderstand human knowledge – and so to constrict it to the narrow scope of the achievably mechanical.

In analytical terms, as I have suggested, modeling has two phases: first, construction; second, manipulation. Examples come readily to mind from ordinary technical practice, e.g., building a relational database, then querying the data thus shaped to explore emergent patterns. As experience with databases shows, the two phases often blur into each other especially in the early stages when use uncovers faults or suggests improvements that direct redesign. A model 0/and a model for may be distinct types – because in our terms they are fixed objects. But modeling of something readily turns into modeling for better or more detailed knowledge of it; similarly, the knowledge gained from realizing a model for something feeds or can feed into an improved version. This characteristic blurring of design into use and use into (re)design is what denies modeling of any sense of closure. Modeling for, Utopian by definition, is denied it in any case.

# Learned Complaints
So far so good – but at the cost of averting our gaze from the problems with the word "model." Indeed, the extensive and growing literature on the topic may seem adrift in a hopeless muddle. "I know of no model of a model", physicist H. J. Groenewold declared many years ago (1960: 98). The philosopher Peter Achinstein has warned us away even from attempting a systematic theory (1968: 203). The word itself is indeed astonishingly polysemous – or promiscuous, as Nelson Goodman puts it. "Model", he complains, can be used to denote "almost anything from a naked blonde to a quadratic equation" (1976: 171). Nevertheless, the word is often used as if its semantic complexity either did not exist or could be safely ignored. The muddle of partly overlapping, partly contradictory senses is proof enough that we ignore it at our peril. Nor can we simply avoid the problem by dismissing "model" altogether, as Goodman and others recommend, without (as I will argue) hobbling our ability to understand inter alia those aspects of computing most important to research – one might even say, as I do, its essence. Despite several other, supposedly less confusing terms on offer, the word remains stubbornly popular in the literature of the social and physical sciences, the history and philosophy of science, cognitive science, artificial intelligence, and related areas.

Theoretical physicist John Ziman and philosopher Stephen Toulmin, for example, recommend "map" on the basis of its conceptual clarity and fitness for describing the relationship between theoretical knowledge and reality ([@Ziman 2000]: 126–38, 147–50; [@Toulmin 1953]: 94–109). Goodman would have us collapse modeling into diagramming, which he thinks less troublesome (1976: 171–3). But preference needs to be based on more than such criteria; "map", for example, serves experiment much less well than theory, as I will show. We require a close and careful look at the semantic fields of all major alternatives, including "map", for their disjunctions and overlaps. We need to scrutinize each of these, asking what does it denote and connote that the others do not, and vice versa? What do all have in common? What are their individual tendencies of mind, and which of these best suits computing as we are learning to conceive it?

# Philological Analysis of Related Terms
So far I have used the term "model" as the default, partly for purposes of convenience, partly because, as I argue, it is right for the job. To answer the learned criticisms and further clarify our topic, however, I propose to question it by comparison against the major alternatives: "analogy", "representation", "diagram", "map", "simulation", and "experiment." As we have seen, the two decisive criteria are that the thing named by the chosen term be computationally tractable and manipulable. Tractability in turn requires complete explicitness and absolute consistency; manipulability resolves into mechanical action and interactivity. Hence the term must denote a continual process of coming to know, not an achievement but an approximation. As I have argued, it is from the difference between the approximation and the reality approximated – which ultimately for the humanities is our humanly known apprehension of that reality – that we learn.

For each of the alternative terms I ask whether and to what degree the word normally denotes a dynamic process and whether it refers to a concrete, i.e. manipulable, form – the requirements of anything whose function is fulfilled through being changed. Corresponding to the two senses of "model" I identified earlier, the denotative model of and the exemplary model for, I also ask whether each word tends to the mimetic (imitation) or proleptic (anticipation). The distinction helps in determining whether the action denoted by a term may be said to be bounded, either by a fixed form, as is the case with "analogy", or by an inherent tendency to reach a definitive or satisfactory conclusion, as in "representation."

Thus bringing "model" into focus against the semantic background of these other terms will show that the problem has not so much been too many meanings for "model" as use without regard to any of them, often as if the sense of it simply goes without saying. It doesn't. But perhaps the most important lesson we learn from seeing the word in the context of its synonym set is not the range and variety of its meanings; rather, again, its strongly dynamic potential. Apart from the popularity of "model" taken at face-value, the word would have little to recommend it (and, as the complainers say, much against it) but for the open-ended present-participial strength of "modeling."[^4] Indeed, the manifest confusion in the literature on the topic may be primarily due to a mistaken preference for the noun – as if getting a model right, and so promoting it to the status of theory, were the point. Modeling has an entirely different role to play. There are several better terms if what one wants is to name a stable conceptualization.

## Analogy
"Analogy" (Gk. ναλoγα, "equality of ratios, proportion") is, like "model", a highly polysemous term with a long and complex career[^5]. John Stuart Mill complained that "no word … is used more loosely, or in a greater variety of senses, than Analogy" (A System of Logic, 1882). Yet Dr Johnson's pithy definition, "resemblance of things with regard to some circumstances or effects", and Mill's even pithier one, "resemblance of relations", give us an idea of why it is so fruitful. From its original meaning in Greek mathematics, analogy specifies a structured relationship between pairs of related quantities, which for convenience may be represented in the form of an equation, "A/B = C/D", read "as A is to B, so C is to D." Extended beyond mathematics to other modes of reasoning, analogy yields a powerful (but still poorly understood) means of inferring from the one relation to the other. Like most of the words in our domain, "analogy" is proleptic, a means of inference, based on conjecture, to something unknown or uncertain. Examples in the history of science are plentiful, e.g., Kepler's discovery of the vis matrix, or cause of planetary motion, by reasoning that as the sun radiated light, so it must also radiate this motive power [@(Gentner 2002)].

Here I wish only to argue two points. The first is that analogy is basic to the entire vocabulary. Although not every model is as strictly based on an analogy as Kepler's, modeling is inherently analogical, with just the features that make the idea attractive for our purposes. Thus we require a structured correspondence between model and artifact, so that by playing with one we can infer facts about the other. (For example, by adjusting choice of words and weightings for a distribution-display across a textual corpus, one can investigate the effect of vocabulary on the interplay of meanings in that corpus.) The second point is that "analogy" is inherently static: it means either a type of relationship or an instance of one, never an object and not, literally or directly, a process. Action is implied in the ratio of quantities – thus Kepler's "as A does B, so C does D" – but acting is not denoted by the analogy. The word has no commonly used verbal form ("analogize" and "analogizing" are rare if not strange). Although an analogy may be algebraically or geometrically expressed and may refer to concrete objects, it itself is abstract.

Because analogy works so well as a way of describing how we often think, efforts to understand acquisition of new knowledge tend to engage with theories of analogy and to propose many mechanisms, e.g., in cognitive science, educational theory, and artificial intelligence [@(Hoffman 1995)]. Because modeling is analogical, this work is potentially relevant to questions raised in computing the artifacts of the humanities. We need to pay attention here.

## Representation
"Representation" in Nelson Goodman's terms is defined by a symbolic denotative correspondence, not likeness or imitation (1976: 3–41)[^6]. In a less philosophically precise sense, however, we may say that "representation" displays strong mimetic tendencies, e.g., in the definition given by the OED: "An image, likeness, or reproduction in some manner of a thing …. A material image or figure; a reproduction in some material or tangible form; in later use esp. a drawing or painting (of a person or thing)." The history of aesthetics from earliest times, in fits and starts of fashion, demonstrates that the copy-theory of representation, though its falsity names its achievement in a *trompe I'oeil*, remains a habit of mind. If in aesthetics, why not in computer science?

A well-attested present participle and a full complement of verbal forms establishes the action of *representing*, but semantically this action is bounded by its relationship to the represented object, whether this be symbolic or imitative.

As with "analogy", the semantic fields of "model" and "representation" clearly overlap, but the situation is more complex because of the mimetic and proleptic kinds of "model." Hence (Platonism aside) we may say that modeling of is representational but not modeling for. In fact a model of is a manipulable variety of representation – which any representation in software would of course be. The crucial difference between model 0/and representation is the quality of the action implied. Unlike representing, modeling of is denied closure, as I noted earlier. It has no satisfactory trompe I'oeil or symbolizing conclusion. If the researcher calls a halt, then the last state of the system, as it were, is better called a "representation."

In the context of computing, the meaning of "representation" is dominated by the subfield of artificial intelligence known as "knowledge representation" (KR). Given the scope of this essay I can do little more than make a few observations, chiefly about the assumptions built into the name and apparently into tendencies in some KR work. In brief, my argument concerning KR is that it needs to be understood as a particularly rigorous control on model-building suitable to that which can be stated in prepositional form.[^7]

To the connotations of "representation" I have already reviewed, KR adds the demarca-tional term "knowledge." The point I wish to draw from current epistemology is a simple one, for which I quote Michael Williams – at length, because the issues are consequential for us:

>>"Knowledge" is an honorific title we confer on our paradigm cognitive achievements …. More generally, "know" is a "success-term", like "win" or "pass" (a test). Knowledge is not just a factual state or condition but a particular normative status. Such statuses are related to appropriate factual states: winning depends on crossing the line before any other competitor. But they also depend on meeting certain norms or standards which define, not what you do do, but what you must or ought to do. To characterize someone's claim as expressing or not expressing knowledge is to pass judgement on it. Epistemic judgements are thus a particular kind of value-judgement ….

>>This normative dimension distinguishes philosophical theories ofknowledge from straightforwardly factual inquiries and explains why demarcational (and related methodological) issues are so significant. Because epistemological distinctions are invidious, ideas about epistemological demarcation always involve putting some claims or methods above others: mathematics above empirical science, empirical science above metaphysics or religion, logic above rhetoric, and so on. Demarcational projects use epistemological criteria to sort areas of discourse into factual and non-factual, truth-seeking and merely expressive, and, at the extreme, meaningful and meaningless. Such projects amount to proposals for a map of culture: a guide to what forms of discourse are "serious" and what are not. Disputes about demarcation – induding disputes about whether demarcational projects should be countenanced at all – are disputes about the shape of our culture and so, in the end, of our lives.

>>(2001: 11–12)

Projects such as Cyc, based on what Northrop Frye characterized as the discredited Wissenscbaft-theory of knowledge – that its accumulation in vast quantities will one day, somehow, result in understanding8 – clearly assume if not perfect closure, then a threshold beyond which lack of perfection ceases to matter. But to whom, and for what purposes?[^9] Apart from such questions, and the serious doubts within computer science on the wisdom of building massive knowledge-bases for expert systems[^10] – there are, again, the very serious demarcational issues. When, for example, one of the leading theorists of KR writes in passing that, "Perhaps there are some kinds of knowledge that cannot be expressed in logic" ([@Sowa 2000]: 12), our intellectual claustrophobia tells an important tale. Not, of course, the only one. If the point of modeling is to fail well, then KR has a vital quality-control function to serve.

## Diagram
A diagram (Gk. διγραμμα, "that which is marked out by lines, a geometrical figure, written list, register, the gamut or scale in music")[^11] is an analogical drawing, "a figure drawn in such a manner that the geometrical relations between the parts of the figure illustrate relations between other objects": thus the physicist James Clerk Maxwell on the graphic, symbolic, and hybrid kinds (1911). Such a diagram ranges from the precisely drawn schematic, whose measurements are significant, to the rough sketch intended to express symbolic relations only. But what makes a graphic a diagram, properly so called, is the way in which it is read, not its resemblance to anything[^12]. Reviel Netz argues the point for the lettered diagram in Greek mathematical texts: "It is only the diagram perceived in a certain way which may function alongside the text" – irrelevant discrepancies are overlooked, the important matters denoted by the lettering: "All attention is fixed upon the few intersecting points, which are named" (1999: 33–5). Even when the diagrammed entity is a physical object, the diagram represents structure and interrelation of essential parts, foregrounding interpretative choice and conscious purpose. The ability to manipulate structures and parts may be implied.

The word "diagram" doubles as noun and verb and has a full range of verbal inflections. Like "represent", its action is bounded, but more by ideas than appearance, even when that appearance is precisely delineated. As Maxwell notes for physics, diagrams often represent force or movement, even if only implicitly, though the form is static. As a means of communication, e.g., in a lecture or discussion between collaborators, diagramming is the point, not the static trace left behind. That trace may in fact be unintelligible apart from the discussion of which it was a dynamic part.

The focus on ideas rather than things per se, the role of manipulation where diagramming is heuristic and the kinaesthetics of the action suggest the close relationship between diagramming and modeling for which Goodman argues. Models of, he declares, "are in effect diagrams, often in more than two dimensions and with working parts … [and] diagrams are flat and static models" (1972: 172–3). Nevertheless, the two-dimensionally graphic, geometrical, and finally static qualities of the diagram define it, not "model", which has considerably broader applications.

Sun-Joo Shin and Oliver Lemon note that although diagramming is very likely one of the oldest forms of communication, modern logicians and philosophers have tended until recently to regard it as only of marginal importance.[^13] That is changing very rapidly now. As a cognitive, reasoning process it is studied in relation to Greek mathematics and geometry in particular [@(Netz 1999)]. Modern philosophical attention can be traced from Descartes's "La Geometric" (1637) and Kant's Critique of Pure Reason II.1.1 (1781) to Peirce's "existential graphs" in the late nineteenth century, significantly as part of his much broader interest in scientific discovery, to which I will return. His work is now central to much current research.

Shin and Lemon delineate three branches of research since the mid-1990s: (1) multi-modal and especially non-linguistic reasoning, in the philosophy of mind and cognitive science; (2) logical equivalence of symbolic and diagrammatic systems, in logic; and (3) heterogeneous systems implementing theories of multi-modal reasoning, in computer science. The close relationship of diagramming and modeling make this research immediately relevant.

# Map
A map may be defined as a schematic spatial representation, or following Maxwell, a diagram of "anything that can be spatially conceived."[^14] Indeed, if not for the geographical focus of mapping, the semantic fields of "map" and "diagram" would completely overlap: both are fully verbal, their action bounded by a graphical representation that has both strongly mimetic and ideational aspects; both manipulate data for specific purposes and introduce fictional elements to serve these purposes. But the long history of mapping the physical world for exploration and description gives "map" specific (and evidently powerful) connotations.

Mapping is particularly characteristic of an early, exploratory period, when a territory is unknown to its discoverers (or conquerors). Mapping constructs the world it represents, selectively, therefore shaping thought and guiding action. It orients the newcomer, giving him or her control of the mapped terrain, at the same time expressing, though perhaps covertly, a perspective, a set of interests, and a history. Mapping attaches meaning to place. Like modeling it can be either of or for a domain, either depicting the present landscape or specifying its future – or altering how we think about it, e.g., by renaming its places. A map is never entirely neutral, politically or otherwise.

As I have noted, John Ziman, following Stephen Toulmin, has argued persuasively for describing scientific research as mapping – hence the immediate relevance of the cartographic imagination to my project. Mapping particularly fits a Kuhnian view of research: long periods of stable activity within a settled terrain interspersed by revolutionary, and perhaps incommensurable, reconceptualizations of that terrain. Mapping is for our purposes more to the point than representation, because we always know that there can be many maps for any territory and that all of them have a fictional character (which is why the map is a standard example of an interpretative genre for data[^15]). But because its action is bounded and its result defines a world, mapping better suits the theoretician's than the experimenter's view.

In computer science, mapping is used in knowledge and argument representation and implementation of schemes for depicting cyberspace in general and the Web in particular. The term surfaces in "Topic Maps", "Concept Maps", and is implicit in talk about, e.g., "semantic networks." This interest seems to originate with Toulmin's mapping of argument [@(Toulmin 1958)], which suggests techniques of automated inferencing in AI. (Maps of argument look like flowcharts.) As a form of data-visualization, mapping also connects with a very strong, recent interest in humanities computing [@(Kirschenbaum 2002)], and so connects this interest with modeling.

## Simulation
"Simulation" is "The technique of imitating the behaviour of some situation or process … by means of a suitably analogous situation or apparatus" *(OED)*.[^16] Its mimetic tendencies and so bounded action are perhaps most emphatic among the terms we are considering. Again, total replication is not at issue; a simulation attends to selected details of the world, thus can be exploratory, as when relevant conditions of flight are simulated for purposes of study or training. Simulation also relies on abstraction from the original to the analogue system (@[Simon 1969]: 15–18), which makes it a kind of representation, subject to the same philosophical argument including the caveat respecting mimesis. But in usage, the connotation, if not denotation, of an exact correspondence between simulation and original remains paradoxically alongside knowledge of real difference.[^17] That knowledge, however uneasily, can be put aside, as in what we now call "virtual reality" (VR).[^18]

In its current form VR is of course quite a recent phenomenon, but the essential movement of simulation on which it is based, from self-conscious imitation to displacement of reality, is attested from the get-go of applied computing, in the weapons research in nuclear physics immediately following World War II. "Proven on the most complex physical problem that had ever been undertaken in the history of science", Peter Galison notes, simulation came to replace experimental reality, thus blurring multiple boundaries that had previously defined research, redefining it in new terms (1997: 690f). Since then the turn away from traditional analytic methods to simulation has spread to several other fields (Burch 2002). As the biologist Glenn W Rowe points out, with this turn has come the realization that "a great many systems seem to have an inherent complexity that cannot be simplified"19 – and so must be studied as simulations. Thus simulation has opened our eyes to the new problems with which it can deal. In the humanities we have known for some years that computer-based simulations, in the form of pedagogical games, can play a role in teaching. An old but very good example is The Would-Be Gentleman, a re-creation of economic and social life in seventeenth-century France in which the student-player must realize and put aside his or her modern preconceptions in order to win (Lougee 1988). In other words he or she must become a seventeenth-century Frenchman mentally and emotionally. From more recent and far more technically advanced VR applications, such as Richard Beacham's and Hugh Denard's reconstruction of the theater of Pompey in Rome (Beacham and Denard 2003), one can predict a scholarly future for simulation in many areas of humanistic research.

Simulation, like game-playing, tends to forgetfulness of the mechanism by which it is created, so long as its terms of engagement (expressed in parameters and algorithms) are fixed. Unfix them – e.g., in The Would-Be Gentleman by allowing the player to change the encoded attitude toward marrying above or below one's station – and the simulation becomes a modeling exercise directed to exploring the question of that attitude. Thus simulation crosses over into modeling when the constants of the system become variables. Modeling, one might say, is a self-conscious simulation, and simulation an assimilated modeling.

Experiment
In common usage "experiment" (L. experiri, to try) is either "An action or operation undertaken in order to discover something unknown …" or "The action of trying anything, or putting it to proof; a test, trial …" (OED). In its broadest sense, the word embraces "modeling", indeed any heuristic experience of the world, especially that which involves conscious purpose, defined procedure, or its material instantiation in equipment. Like "modeling", "experiment" refers to a process whose ending is constructed rather than given: as Peter Galison has argued for the physical sciences, the experimenter decides if and when the attempt has succeeded or failed, in "that fascinating moment … when instrumentation, experience, theory, calculation, and sociology meet" (Galison 1987: 1). Modeling and experimenting are by nature open-ended; indeed they are often at the time ill-defined, even quite messy.20

The semantic overlap of "modeling" and "experiment" is so close that the two can be quite difficult to separate (Guala 2002). Mary S. Morgan, writing about modeling in economics, has argued that they may be discriminated by the degree to which the former involves hypothesis, the latter reality (2002: 49). But, as she notes, hybrids provide exceptions and thought experiments – "devices of the imagination used to investigate nature" (Brown 2002) – a very close analogue to modeling.21 Perhaps the relationship is most clearly stated by saying that in the context of research a model is an experimental device, modeling an experimental technique.

The point of considering "experiment" here is, however, primarily to locate our topic within the context of a particular history of ideas and so to engage with large and important areas of historical and philosophical research. Indeed, as an experimental technique modeling has shared the fate of experiment in the specialist literature, and so also in the popular understanding. Allow me briefly to summarize the background.22

By the mid-nineteenth century, understanding of scientific work had begun to polarize into two epistemological conditions, which physicist and philosopher Hans Reichenbach later famously named "the context of discovery" and "the context of justification."23 By the early to mid-twentieth century, attention had shifted almost completely to justification and so, as Thomas Nickels has said, discovery was expelled from mainstream epistemology (2000: 87). Experiment, the means of discovery, was in consequence also demoted and theory, the focus of justification, promoted. "The asymmetric emphasis on theory in the historical literature", Peter Galison explains, meant that attention was confined "to the invention and testing of theories" (1987: 8), the actual conduct and intellectual role of experiments being largely overlooked. In philosophy too, "experiment for theory" dominated until (in Ian Hacking's paraphrase of Nietzsche) Thomas Kuhn's The Structure of Scientific Revolutions "unwrapped the mummy of science" by historicizing it (Hacking 1983: If) – What had actually always been happening in experimental work could then become a proper subject of investigation. Furthermore, Kuhn's ample demonstration of "the essential role theory plays in the conduct of experimentation, the interpretation of data, and in the definition of 'relevant' phenomena" depolarized theory and experiment (Galison 1987: 80- In other words, from an entirely subordinate and observational role, experiment emerged alongside theory as an interdependent partner.

Subsequently, through the work of Hacking, Feyerabend, Galison, and several others, the fiction of a unitary "scientific method", in which theory cleanly defines the role of experiment, has been dispelled. As Hacking says, calling for a "Back-to-Bacon" movement, "Experiment has a life of its own" (1983: 150), sometimes preceded by theory, sometimes not. But the consequent liberation of experiment from the debilitating pretense of grubby handmaiden to "pure" theory has at the same time directed attention back to the very hard, old problem of discovery: how does this happen?

Conclusion
Why do we need an answer to this question? Because, I have argued, ours is an experimental practice, using equipment and instantiating definite methods, for the skilled application of which we need to know what we are doing as well as it can be known. I have labeled the core of this practice "modeling", and suggested how, properly understood, modeling points the way to a computing that is of as well as in the humanities: a continual process of coming to know by manipulating representations. We are, I have suggested, in good epistemological company. But this only sharpens the epistemological question. The signified of modeling vanishes into the murk because we lack a disciplined way of talking about it. Methods are explicit, actions definite, results forthcoming, yet we have been unable fully and persuasively to articulate the intellectual case for the means by which these results are produced. Hence the just-a-tool status of computing, the not-a-discipline slur, the tradesman's entrance or other back door into the academy. No one doubts the usefulness of the practice. Rather it's the intellection of praxis to which the next stage in the argument I have begun here must turn.

# Note

[^1] My definitions reflect the great majority of the literature explicitly on modeling in the history and philosophy of the natural sciences, especially of physics (Bailer-Jones 1999). The literature tends to be concerned with the role of modeling more in formal scientific theory than in experiment. The close relationship between modeling and experimenting means that the rise of a robust philosophy of experiment since the 1980s is directly relevant to our topic; see Hacking (1983); Gooding (2000). Quite helpful in rethinking the basic issues for the humanities are the writings from the disciplines other than physics, e.g., Clarke (1972) on archaeology; Wimsatt (1987) on biology; Del Re (2000) on chemistry; and on the social sciences, the essays by de Callatay, Mironesco, Burch, and Gardin in Franck (2002). For interdisciplinary studies see Shanin (1972) and Morrison and Morgan (1999), esp. "Models as Mediating Instruments" (pp. 10–37). For an overview see Lloyd (1998).

[^2] Cf. Goodman's distinction between "denotative" and "exemplary" models, respectively (1976: 172–3); H. J. Groenewold's "more or less poor substitute" and "more or less exemplary ideal" (1960: 98). Similar distinctions are quite common in the literature.

[^3] This is usually done in "the rhetoric of technohype … the idiom of grant proposals and of interviews in the Tuesday New York Science Times: The breakthrough is at hand; this time we've got it right; theory and practice will be forever altered; we have really made fantastic progress, and there is now general agreement on the basics; further funding is required" (Fodor 1995). More serious criticism is leveled by Terry Winograd (1991: 207–8); see below.

[^4] I have in mind the present-participial imagination described by Greg Dening, with which we may "return to the past the past's own present, a present with all the possibilities still in it, with all the consequences of actions still unknown" (Dening 1998: 48; see also Dening 1996: 35–63).

[5^] For the concept in imaginative language and thought see Gibbs (1994; reviewed by Turner 1995), Turner (1996); in computer science, Hoffman (1995) – whose summary of research is quite valuable; in cognitive science, including psychology, Mitchell (1993), Holyoak and Thagard (1997); in the philosophy of science, Achinstein (1968), Leatherdale (1974), Gentner (2002), Shelley (2002); in relation to modeling, Bailer-Jones (1999), Bailer-Jones and Bailer-Jones (2002). I do not deal here with metaphor in relation to modeling, for which see Black (1979), Johnson (2002).

[^6] Goodman dismantles the copy-theory of representation, arguing that representation is not mimetic but symbolic: object X is always represented as Y, which means that Y is selective with respect to X and stands in symbolic relationship to it. See also Elgin (1998), Hopkins (2000).

[^7] Possibly the best and least problematic view is afforded by Davis et al. (1993); see also Sowa (2000); Barr and Feigenbaum (1981). Lenat (1998) illustrates the problematic tendencies in this field; Winograd (1991) and Dreyfus (1985) provide the antidote.

[^8] Frye (1991: 4), to which compare Winograd's analysis of the "almost childish leap of faith" made, e.g., by Marvin Minsky in his "Society of Mind" thesis that "the modes of explanation that work for the details of [the artificial micro-worlds thus represented] will be adequate for understanding conflict, consciousness, genius, and freedom of will" (Winograd 1991: 204–7) – as the ambitious claim; see also Winder (1996).

[^9] Note the boast that "Cyc knows that trees are usually outdoors, that once people die they stop buying things, and that glasses of liquid should be carried rightside-up" (Cycorp Company Overview, at http://www.cyc.com/overview.html, accessed September 22, 2003.

[^10] Winograd and Flores (1986: 97–100, 131–3, 174–7); Dreyfus (1985). See also Brooks (1991).

[^11] See, however, the discussion in Netz (1999: 35–8).

[^12] Goodman (1976: 170f), who distinguishes between analogue and digital diagrams. As Netz explains, the lettered diagram provides a good example of the latter (1999: 34f).

[^13] Shin and Lemon (2002); note the extensive bibliography.

[^14] Robinson and Petchenik (1976); see also Monmonier (1996); Wood (1992). Turnbull (1994) argues specifically for the link between maps and theories.

[^15] See Bateson (2002: 27–8), who cites Alfred Korzybski's principle that "the map is not the territory" (Korzybski 1933) and points out that "the natural history of human mental process" nevertheless tells a different tale: part of us in fact regularly identifies map and territory, name and thing named. See also Goodman (1972: 15); Kent (2000/1978: xix).

[^16] On the semantic overlap of "simulation" with "experiment" and "model", see Guala (2002), who also stresses the necessity of including the designer or initiator as part of the simulation.

[^17] Hence, perhaps, the deception attributed to the word: "intent to deceive" in a "false assumption or display, a surface resemblance or imitation …" (OED 1 .a., 2) – an animated trompe l'oeil.

[^18] Recent research in psychology and cognitive science, working with the representational model of mind, might be summarized by the proposition that reality as we know and participate in it is simulated. Thus mental simulation is used to explain aspects of cognition (see, e.g., Markman and Dietrich 2000; Davies and Stone 2000). Especially relevant here is the idea that perceptual simulations play a significant role in cognition, as when the replay of a kinaesthetic memory, awakened by some corresponding movement or gesture, lends meaning to a diagram or physical model. This is why animations can in principle be more effective than static diagrams: they are more knowledgeable (Craig et al. 2002)

19 Rowe (1994), quoted by Burch (2002: 245); see also Winsberg (2001).

20 This is true for scientific experiment much more often and more significantly than popular and earlier philosophical accounts would have us believe. Ian Hacking illustrates the point in an illuminating discussion of the famous Michelson-Morley experiment, "a good example of the Baconian exploration of nature" (1983: 254); see his discription (1983: 253–61), and esp. the book as a whole. See also Gooding (2000) and Morrison (1998) for an overview of experiment in current philosophy of science; the triplet of articles presented at a symposium on "The Philosophical Significance of Experimentation", Hacking (1988), Heelan (1988), and Galison (1988); and Franklin (2002) for physics in particular.

21 See also Brown (2000), Gooding (1998) and note esp. the careful argument in Kuhn (1964) toward an understanding of how thought experiment can lead to new knowledge, not simply expose logical contradictions or confusions.

22 I rely primarily on Galison (1987), Hacking (1983) and Nickels (2000).

23 Reichenbach introduced the distinction to mark "the well-known difference" between "the form in which thinking processes are communicated to other persons [and] the form in which they are subjectively performed", i.e., justification and discovery, respectively (Reichenbach 1938, chapter 1); compare Feyerabend (1993: 147–58). This distinction involves a long-standing argument that goes back to the debate between William Whewell (first to use the term "philosophy of science") and John Stuart Mill; it was then taken up by Charles Sanders Peirce on the one hand and Karl Popper on the other. Popper, in Logik der Forschung (translated as The Logic of Scientific Discovery) characteristically ruled discovery out of court by identifying it as a matter for psychology, recalling Duhem's and Reichenbach's use of that term: "The question of how it happens that a new idea occurs to a man … may be of great interest to empirical psychology; but it is irrelevant to the logical analysis of scientific knowledge" (Popper 1959/1935: 7). See Nickels (2000).

Works Cited
Achinstein, Peter (1968). Concepts of Science: A Philosophical Analysis. Baltimore: Johns Hopkins University Press.

Bailer-Jones, Daniela M. (1999). Tracing the Development of Models in the Philosophy of Science. In Magnani, Nersessian and Thagard (1999): 23–40.

Bailer-Jones, Daniela M. 2002. Models, Metaphors and Analogies. In Machamer and Silberstein (2002): 108–27.

Bailer-Jones, Daniela M. and Coryn A. L. Bailer-Jones (2002). Modeling Data: Analogies in Neural Networks, Simulated Annealing and Genetic Algorithms. In Magnani and Nersessian (2002): 147–65.

Barr, Avron and Edward A. Feigenbaum (1981). Representation of Knowledge. In The Handbook of Artificial Intelligence. Volume I, ed. Avron Barr and Edward A. Feigenbaum (pp. 141–222). Los Altos, CA: Morgan Kaufmann.

Bateson, Gregory (2002). Mind and Nature: A Necessary Unity. Cresskill, NJ: Hampton Press.

Beacham, Richard, and Hugh Denard (2003). The Pompey Project: Digital Research and Virtual. Reconstruction of Rome's First Theatre. Computers and the Humanities 37, 1: 129–39.

Black, Max (1979). More About Metaphor. In Metaphor and Thought, ed. Andrew Ortony (pp. 19–39). Cambridge: Cambridge University Press.

Brooks, Rodney A. (1991). Intelligence without Representation. Artificial Intelligence Journal 47: 139–59.

Brown, James Robert (2000). Thought Experiments. In Newton-Smith (2000): 528–31.

Brown, James Robert 2002. Thought Experiments. Stanford Encyclopedia of Philosophy. Accessed September 12, 2003. At <http://plato.stanford.edu/entries/thought-experiment/>.

Burch, Thomas K. (2002). Computer Modeling of Theory: Explanation for the 21st Century. In Franck (2002): 245–65.

Cartwright, Nancy (1983). How the Laws of Physics Lie. Oxford: Clarendon Press.

Clarke, David L. (1972). Models and Paradigms in Contemporary Archaeology. In Models in Archaeology, ed. David L. Clarke (pp. 1–60). London: Methuen.

Craig, David L., Nancy J. Nersessian, and Richard Catrambone (2002). Perceptual Simulation in Analogical Problem Solving. In Magnani and Nersessian (2002): 167–89.

Davies, Martin and Tony Stone (2000). Simulation Theory. In Routledge Encyclopedia of Philosophy. London: Routledge.

Davis, Randall, Howard Shrobe, and Peter Szolovits (1993). What Is Knowledge Representation? AI Magazine(Spring): 17–33. Accessed September 18, 2003. At <http://www.aaai.org/Library/Magazine/Voll4/l4 01.html>.

Del Re, Giuseppe (2000). Models and Analogies in Science. Hyle - International Journal for the Philosophy of Chemistry 6, 1: 5–15. Accessed September 18, 2003. At http://www.hyle.Org/journal/issues/6/delre.htm.

Dening, Greg (1996). Performances. Chicago: University of Chicago Press.

Dening, Greg (1998). Readings/Writings. Melbourne: University of Melbourne Press.

Dreyfus, Hubert L. (1985). From Micro-Worlds to Knowledge Representation: AI at an Impasse. In Readings in Knowledge Representation, ed. Ronald J. Brachman and Hector Levesque (pp. 71–94). Los Altos, CA: Morgan Kaufmann.

Elgin, Catherine Z. (1998). Goodman, Nelson. In Routledge Encyclopedia of Philosophy. London: Routledge.

Fetzer, James H. (1999). The Role of Models in Computer Science. The Monist 82, 1: 20–36.

Feyerabend, Paul (1993). Against Method, 3rd edn. London: Verso.

Finley, M. I. (1986). Ancient History: Evidence and Models. New York: Viking.

Fodor, Jerry (1995). West Coast Fuzzy. Review of Paul M. Churchland, The Engine of Reason, the Seat of the Soul. Times Literary Supplement (August 25).

Franck, Robert, (ed.) (2002). The Explanatory Power of Models. Methodos Series, vol. 1. Dordrecht: Kluwer Academic.

Franklin, Allan (2002). Experiment in Physics. The Stanford Encyclopedia of Philosophy. Accessed September 12, 2003. At <http://plato.stanford.edu/entries/physics-experiment>.

Frye, Northrop (1991). Literary and Mechanical Models. In Research in Humanities Computing 1. Papers from the 1989 ACH-ALLC Conference, ed. Ian Lancashire (pp. 1–12). Oxford: Clarendon Press.

Galison, Peter (1987). How Experiments End. Chicago: University of Chicago Press.

Galison, Peter (1988). Philosophy in the Laboratory. Journal of Philosophy 85, 10: 525–7.

Galison, Peter (1997). Image and Logic: A Material Culture of Microphysics. Chicago: University of Chicago Press.

Geertz, Clifford (1973). Religion as a Cultural System. In The Interpretation of Cultures: Selected Essays. New York: Basic Books. (Reprint: London: Fontana Press, 1993.).

Gentner, Dedre (2002). Analogy in Scientific Discovery: The Case of Johannes Kepler. In Magnani and Nersessian (2002): 21–39.

Gibbs, Raymond W, Jr (1994). The Poetics of Mind: Figurative Thought, Language, and Understanding. Cambridge: Cambridge University Press.

Gooding, David C. (1998). Thought Experiments. Routledge Encyclopedia of Philosophy. London: Routledge.

Gooding, David C. (2000). Experiment. In Newton-Smith (2000): 117–26.

Goodman, Nelson (1972). Problems and Projects. Indianapolis, IN: Bobbs-Merrill.

Goodman, Nelson (1976). The Languages of Art. Indianapolis, IN: Hackett.

Groenewold, H. J. (1960). The Model in Physics. In The Concept and the Role of the Model in Mathematics and the Natural Sciences, ed. Hans Friedenthal (pp. 98–103). Dordrecht: D. Reidel.

Guala, Francesco (2002). Models, Simulations, and Experiments. In Magnani and Nersessian (2002): 59–74.

Hacking, Ian (1983). Representing and Intervening: Introductory Topics in the Philosophy of Natural Science. Cambridge: Cambridge University Press.

Hacking, Ian (1988). On the Stability of the Laboratory Sciences. Journal of Philosophy 85, 10: 507–14.

Heelan, Patrick A. (1988). Experiment and Theory: Constitution and Reality. Journal of Philosophy 85, 10: 515–27.

Hoffmann, Robert R. (1995). Monster Analogies. AI Magazine 16, 3: 11–35. Accessed September 18, 2003. At <http://www.aaai.org.Library/Magazine/Vol16.16 03/vol.16 03.html>.

Holyoak, Keith J. and Paul Thagard (1997). The Analogical Mind. American Psychologist 52, 1: 35–44.

Hopkins, R. D. (2000). Depiction. In Routledge Encyclopedia of Philosophy. London: Routledge.

Johnson, Mark (2002). Metaphor-Based Values in Scientific Models. In Magnani and Nersessian (2002): 1–19.

Kent, William (2000/1978). Data and Reality, 2nd edn. Bloomington, IN: 1st Books. (Originally published in Amsterdam: North Holland.).

Kirschenbaum, Matthew, (ed.) (2002). Image-Based Humanities Computing. Special issue of Computers and the Humanities 36, 3.

Korzybski, Alfred (1933). Science and Sanity: An Introduction to Non-Aristotelian Systems and General Semantics. Lancaster, PA: International Non-Aristotelian Library Publishing.

Kuhn, Thomas (1964). A Function for Thought Experiments. In L'aventure de la science, Mélanges Alexandre Koyré, vol. 2 (pp. 307–34). Paris: Hermann.

Leatherdale, W. H. (1974). The Role of Analogy, Model and Metaphor in Science. Amsterdam: North Holland Publishing.

Leff, Gordon (1972). Models Inherent in History. In Shanin, ed.(1972):148–74.

Lenat, Douglas B. (1998). From 2001 to 2001: Common Sense and the Mind of HAL. In HAL's Legacy: 2001's Computer as Dream and Reality, ed. David G. Stork (pp. 193–209). Cambridge, MA: MIT Press.

Lloyd, Elisabeth A. (1998). Models. In Routledge Encyclopedia of Philosophy. London: Routledge.

Lougee, Carolyn (1988). The Would-Be Gentleman: a Historical Simulation of the France of Louis XIV. History Microcomputer Review 4: 7–14.

McCarty, Willard (2002). A Network with a Thousand Entrances: Commentary in an Electronic Age? In The Classical Commentary: Histories, Practices, Theory, ed. Roy K. Gibson and Christina Shuttleworth Kraus (pp. 359–402). Leiden: Brill.

Machamer, Peter and Silberstein, Michael, eds. (2002). The Blackwell Guide to the Philosophy of Science. Oxford: Blackwell Publishers.

Magnani, Lorenzo and Nancy J. Nersessian, (eds.) (2002). Model-Eased Reasoning: Science, Technology, Values. New York: Kluwer Academic/Plenum.

Magnani, Lorenzo, Nancy J. Nersessian, and Paul Thagard, (eds.) (1999). Model-Eased Reasoning in Scientific Discovery. New York: Kluwer Academic/Plenum.

Markman, Arthur B. and Eric Dietrich (2000). Extending the Classical View of Representation. Trends in Cognitive Sciences 4, 12: 470–5.

Maxwell, James Clerk (1911). Diagram. In Encyclopaedia Britannica, 11th edn. (pp. 146–9).

Minsky, Marvin (1991). Conscious Machines. Proceedings, National Research Council of Canada, 75th Anniversary Symposium on Science in Society (June). Accessed April 22, 2004. At <http://kuoi.asui.uidaho.edu/~kamikaze/doc/minsky.html>.

Minsky, Marvin L. (1995). Matter, Mind and Models. Accessed January 20, 2003. At http://medg.lcs.mit.edu/people/doyle/gallery/minsky.mmm.html>. (Rev. version of the essay in Semantic Information Processing, ed. Marvin Minsky. Cambridge, MA: MIT Press, 1968.).

Mironesco, Christine (2002). The Role of Models in Comparative Politics. In Franck (2002): 181–95.

Mitchell, Melanie (1993). Analogy-Making as Perception. Cambridge, MA: MIT Press.

Monmonier, Mark (1996). How to Lie with Maps, 2nd edn. Chicago: University of Chicago Press.

Morgan, Mary S. (2002). Model Experiments and Models in Experiments. In Magnani and Nersessian (2002): 41–58.

Morrison, Margaret (1998). Experiment. In Routledge Encyclopedia of Philosophy. London: Routledge.

Morrison, Margaret and Mary S. Morgan, (eds.) (1999). Models as Mediators: Perspectives on Natural and Social Science. Ideas in Context, 52. Cambridge: Cambridge University Press.

Netz, Reviel (1999). The Shaping of Deduction in Greek Mathematics: A Study in Cognitive History. Ideas in Context, 51. Cambridge: Cambridge University Press.

Newton-Smith, W. H. ed. (2000). A Companion to the Philosophy of Science. Oxford: Blackwell.

Nickels, Thomas (2000). Discovery. In Newton-Smith (2000): 85–96.

Polanyi, Michael (1966). The Tacit Dimension. New York: Doubleday.

Popper, Karl R. (1959/1935). The Logic of Scientific Discovery. London: Hutchinson. (Originally published as Logik der Forschung. Vienna: Verlag von Julius Springer.).

Popper, Karl R. (1979). Objective Knowledge. An Evolutionary Approach. Oxford: Clarendon Press.

Reichenbach, Hans (1938). Experience and Prediction: An Analysis of the Foundations and the Structure of Knowledge. Chicago: University of Chicago Press. (A transcription of Chapter 1 is available at http://www.ditext.com/reichenbach/reicho.html. Accessed September 12, 2003.).

Robinson, Arthur H. and Barbara Petchenik (1976). The Nature of Maps. Chicago: University of Chicago Press.

Rowe, Glenn W. (1994). Theoretical Models in Biology: The Origin of Life, the Immune System, and the Brain. Oxford: Oxford University Press.

Shanin, Teodor (1972). Models in Thought. In Shanin, ed. (1972): 1–22.

Shanin, Teodor, (ed.) (1972). Rules of the Game: Cross-Disciplinary Essays on Models in Scholarly Thought. London: Tavistock.

Shelley, Cameron (2002). Analogy Counterarguments and the Acceptability of Analogical Hypotheses. British Journal for the Philosophy of Science 53: 477–96.

Shin, Sun-Joo and Oliver Lemon (2002). Diagrams. Stanford Encyclopedia of Philosophy. Accessed September 11, 2003. At http://plato.stanford.edu/entries/diagrams/.

Simon, Herbert (1969). The Sciences of the Artificial. Cambridge, MA: MIT Press.

Smith, Brian Cantwell (1995/1985). Limits of Correctness in Computers. In Computers, Ethics and Social Values, ed. Deborah G. Johnson and Helen Nissenbaum (pp. 456–69). Englewood Cliffs, NJ: Prentice Hall. (Originally published in Computers and Society (ACM SIGCAS) 14/15: 18–26.).

Sowa, John F. (2000). Knowledge Representation: Logical, Philosophical, and Computational Foundations. Pacific Grove, CA: Brooks/Cole.

Toulmin, Stephen (1953). The Philosophy of Science. London: Hutchinson University Library.

Toulmin, Stephen (1958). The Uses of Argument. Cambridge: Cambridge University Press.

Turnbull, David (1994). Maps are Territories. Science is an Atlas. Chicago: University of Chicago Press.

Turner, Mark (1995). Review of The Poetics of Mind: Figurative Thought, Language, and Understanding, by Raymond W. Gibbs. Pragmatics and Cognition 3, 1: 179–85.

Turner, Mark (1996). Literary Mind: The Origins of Thought and Language. Oxford: Oxford University Press.

Williams, Michael (2001). Problems of Knowledge: A Critical Introduction to Epistemology. Oxford: Oxford University Press.

Wimsatt, William C. (1987). False Models as Means to Truer Theories. In Neutral Models in Biology, ed. Matthew H. Nitecki and Antoni Hoffman (pp. 23–55). Oxford: Oxford University Press.

Winder, William (1996). Textpert Systems. Text Technology 6, 3. Rpt. 1997, Computing in the Humanities Working Papers B.35. Accessed September 11, 2003. At http://www.chass.utoronto.ca/epc/chwp/winder2/.

Winograd, Terry (1991). Thinking Machines: Can There Be? Are We? In The Boundaries of Humanity: Humans, Animals, Machines, ed. James J. Sheehan and Morton Sosna (pp. 198–223). Berkeley: University of California Press.

Winograd, Terry and Fernando Flores (1986). Understanding Computers and Cognition: A New Foundation for Design. Boston: Addison-Wesley.

Winsberg, Eric (2001). Simulations, Models, and Theories: Complex Physical Systems and Their Representations. Philosophy of Science (Proceedings) 68: S442–S454.

Wood, Denis (1992). The Power of Maps. Mappings: Society/Theory/Space. London: Guilford Press.

Ziman, John (2000). Real Science: What it Is, and What it Means. Cambridge: Cambridge University Press.y