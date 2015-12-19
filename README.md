# GTD-Kanban
## Life Organizer, based on "Getting Things Done" and Kanban

Purpose: To create a software tool for creative people to organize and track various aspects of their lives, including projects. This is conceptually based on two works: David Allen's book ["Getting Things Done"](https://en.wikipedia.org/wiki/Getting_Things_Done) and the Kanban methodology for managing projects, in particular the description of Kanban outlined in ["Personal Kanban"](http://www.personalkanban.com/) by Jim Benson and Tonianne DeMaria Barry.

###Getting Things Done
One thesis in "Getting Things Done" is that if your mind has more than one problem to solve, you will not be effective at solving any of them until you have put them into a "trusted system". Once you have done this, your mind is clear to focus on one problem at a time. GTD has a [workflow](https://en.wikipedia.org/wiki/Getting_Things_Done#/media/File:GTDcanonical.png) for processing all of the tasks, ideas, problems, and goals ("issues") in your mind.

If an issue **is not** actionable, you classify it as one of the following:
-  Trash
-  Someday Maybe list
-  Reference list

If an issue **is** actionable, the next question is whether it requires only single step to complete (a *task*), or not (a *project*). If it is a *task*
- If it will take "two minutes", then do it now.
- and it will take more time, then either
  - delegate it, in which case it goes into a "waiting for" list
  - defer it, in which case it either
    - goes into your calendar, to be done at a specific time, or
    - goes into "Next Actions" list, to be done as soon as it can

If an issue is a *project*, then the next steps are
  - put it into the *projects* to plan list, and
  - once planned, review it for *tasks*, as outlined above

###Kanban
The *project* level is where the GTD-Kanban system will transition from GTD to Kanban. Kanban operates on two principles:
  - **visualize your work**, and
  - **limit your work in progress**

In order to **visualize your work**, *projects* are tracked on a board (this could be a whiteboard, piece of paper, or software UI). There are three columns to show the progress of *tasks*:
  - *Ready*
  - *Doing*
  - *Done*

*Tasks* are depicted on a moveable medium (e.g., a Post-It for whiteboards and paper, a draggable window in a software UI). As a task progresses, it is moved from one column to the next.

Using GTD, you will likely have a large backlog of *tasks* and *projects*. In order to **limit your work in progress**, it is important to identify only a few of these that you can realistically be working on, and then represent these on the Kanban board; these will be the rows that cross the *Ready, Doing, Done* columns. The benefit of this approach is that it keeps you focused on a manageable subset of *tasks* and *projects* until they are complete **before** starting in on another one. Once one *task* or *project* is *Done*, it is dropped off the board, and another one brought on.

##Use Cases
Some typical use cases that this tool are intended to address are:
  - You have lots of ideas that you want to act on, you don't want to lose any of them, but can only focus on one at a time
  - You have multiple goals, and want to make incremental progress on all of them in an organized way
  - You are writing a complex piece of software
  - You are writing a book
  - Small issues derail you from focusing on larger goals
  - You are researching a purchase, and are collecting disparate information that you wish to review
  - You are involved in a legal process that includes multiple steps that play out over time. Examples include:
    - Filing income taxes, where you need to pull together multiple pieces of information
    - Filing a patent, where you need to complete multiple sections, do research, and act by certain dates
    - Fighting unjust parking and/or traffic tickets
    - Negotiating a legal agreement

Once you have completed a project once, if you developed a useful technique (e.g. a flow diagram or standard operating procedure), the tool should allow you to describe and store this. This is often true for legal processes.

Getting an overview that enables abstracting multiple issues such that a common solution may move several issues forward. This is often true when writing software

Track progress and successes

## Implementation Details
It is proposed to store the files created with this tool in [JSON format](http://www.json.org/). The intent of using the JSON format is make the work product as portable and accessible as possible. Also, the JSON format used should allow for one JSON file to reference another. A later version should enable the JSON to be loaded into a database for advanced querying. It should be possible to associate tags with all JSON objects so that disparate objects can be recalled together. It is proposed to track changes in the JSON work product of the tool using the Git version control tool, as this supports both local and server based tracking. Such tracking will enable user to view their historical progress tracking their lives.

It is proposed to write the initial code in C++. This leaves open the question of how to implement the UI for presenting the information. Here there are several options, among them using the cross-platform Qt development tools, using [node.js](https://nodejs.org/en/about/) as an interface bewteen the C++ and a web UI front-end on a server, or porting the code to Java. The C++ code will make extensive use of [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) and the [Boost libraries](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)).
