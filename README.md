Copyright (c) 2015 Frederick S. Ziegler

# GTD-Kanban

`"I must create a system or be enslaved by another man's; I will not reason and compare: my business is to create."`

`--William Blake`

##1 Life Organizer, based on "Getting Things Done" and Kanban

Purpose: To create a software tool for creative people to organize and track various aspects of their lives, including projects. This is conceptually based on two works: David Allen's book ["Getting Things Done"](https://en.wikipedia.org/wiki/Getting_Things_Done) and the Kanban methodology for managing projects, in particular the form of Kanban outlined in ["Personal Kanban"](http://www.personalkanban.com/) by Jim Benson and Tonianne DeMaria Barry. This tool is intended to empower the individual.

### 1.1 Getting Things Done
`"Plans are worthless, but planning is everything"`

`--Dwight D. Eisenhower`

One thesis in "Getting Things Done" ("GTD") is that if your mind has more than one problem to solve, you will not be effective at solving any of them until you have put them into a "**trusted system**". This clears your mind to focus on one problem at a time. GTD has a [workflow](https://en.wikipedia.org/wiki/Getting_Things_Done#/media/File:GTDcanonical.png) for processing all of the tasks, ideas, problems, and goals ("issues") in your mind. A useful open-source brain-storming software tool for collecting all these issues is [FreeMind](http://freemind.sourceforge.net/wiki/index.php/Main_Page).

####1.1.a GTD Workflow
In GTD, you start by identifying and classifying all of your issues. These start in your **In-basket**. If an issue **is not** actionable, you place it into one of the following:
-  **Trash**
-  your **Someday Maybe** list
-  your **Reference** list

at which point you ignore it, at least until some later date.

If an issue **is** actionable, the next question is whether it requires only a single step to complete (a ***task***), or multiple steps (a ***project***). If an issue is a ***task***
- if it will take "two minutes", then do it now
- if it will take more time, then either
  - delegate it, in which case it goes into your **Waiting for Another Person** list
  - defer it, in which case it either
    - goes into your **Calendar**, to be done at a specific time, or
    - goes into your **Next Actions** list, to be done as soon as it can

If an issue is a ***project***, then put it into your **Projects-to-Plan** list. When you do plan your projects, the results go into your **Project Plans** list and, from here, you identify actionable **tasks** that can be moved into your **Next Actions** list. If a project contains many dependencies (i.e. multiple steps are dependent on other steps being completed), then a Gannt chart tool, such as the open-source [GanntProject](http://www.ganttproject.biz/) software tool may be helpful.

Once you have processed your issues, you will have the following lists stored in your trusted system:
- your **Someday Maybe** list
- your **Reference** list
- your **Waiting for Another Person** list
- Tasks in your **Calendar** on specific dates
- your **Projects-to-Plan** list
- your **Project Plans** list
- your **Next Actions** list

Only your **Project Plans** and **Next Actions** lists contain **tasks** to work on at this point.

#####1.1.a.i  Planning Projects
How to plan projects in your **Projects-to-Plan** list is beyond the scope of this tool. As a creative person, you probably have your own way of doing this. Two general approaches are [top-down design and bottom-up design](https://en.wikipedia.org/wiki/Top-down_and_bottom-up_design). A good way to start is to write down your objectives; a more formal way is to follow [Design by Contract](https://en.wikipedia.org/wiki/Design_by_contract) methodology. The GTD-Kanban tool will allow you to link planning files (e.g., documents, spreadsheets, diagrams, URLs, etc.) to any ***projects*** and ***tasks***.

###1.2 Kanban
`"Strategy without tactics is the slowest route to victory. Tactics without strategy is the noise before defeat."`

`--Sun Tzu`

Your **Project Plans** and **Next Actions** lists are where the GTD-Kanban system will transition from GTD to Kanban. Kanban operates on two principles:
  - **Visualize your work**, and
  - **Limit your work in progress**

In order to **visualize your work**, ***tasks*** are tracked graphically on a **board**. This could be a whiteboard, piece of paper, or software UI. Generally, ***projects*** are too large to focus on, so ***tasks*** migrate first from the **Project Plans** list to the **Next Actions** list, and then onto the **board**. There are three columns to show the progress of a ***task***:
  - *Ready*
  - *Doing*
  - *Done*

***Tasks*** are depicted on a moveable medium (e.g., a Post-It for whiteboards and paper, a draggable window in a software UI). As a task progresses, it is moved from one column to the next. Once a ***task*** is *Done*, it is removed and another placed in the *Ready* column.

Using GTD, you will likely have a large backlog of ***tasks*** and ***projects***. In order to **limit your work in progress**, it is important to identify only a few of these that you can realistically be working on (the authors of "Personal Kanban" recommend starting with three), and then represent these on the Kanban board; these will be the rows that cross the *Ready, Doing, Done* columns. The benefit of this approach is that it keeps you focused on a manageable subset of ***tasks*** until they are complete *before* starting in on another one. Once one ***task*** is *Done*, it is dropped off the board, and another one brought on.

##2 Use Cases
Some typical use cases that this tool are intended to address are:
  - You have lots of ideas that you want to act on, you don't want to forget any of them, but can only focus on one at a time
  - You have multiple goals, and want to make incremental progress on all of them in an organized way
  - Small issues derail you from focusing on larger goals
  - You are writing a complex piece of software
  - You are building something
  - You are inventing something new
  - You are learning a new subject
  - You are writing a book
  - You want to track your car maintenance plan (e.g., changing fluids regularly)
  - You want to clean out your garage or storage
  - You want to give stuff you don't need to charity
  - You want to repaint or remodel your home
  - You are researching a purchase, and are collecting disparate information that you wish to review
  - You are involved in a legal process that includes multiple steps that play out over time. Examples include:
    - Filing income taxes, where you need to pull together multiple pieces of information
    - Filing a patent, where you need to complete multiple sections, do research, and act by certain dates
    - Fighting unjust parking and/or traffic tickets
    - Negotiating a legal agreement
  - You are starting a business
  - You are doing many/all of the above

Once you have completed a project, if you developed a useful technique (e.g. a flow diagram or standard operating procedure), the tool should allow you to describe and store this. This is often true for legal processes.

Getting an overview may enable you to boil multiple issues down to a single one, resulting in a common solution and moving all these issues forward at once. This is often true when writing software.

You may get satisfaction by keeping a record of the *Done* tasks.

##3. Implementation Details
Files created with this tool will be stored in [JSON format](http://www.json.org/). The intent of using JSON is to make the work product as portable and accessible as possible. The JSON format used will allow for one JSON file to reference another. Changes in the tool's JSON work product may be tracked using the Git version control tool, as this supports both local and server based tracking. Such tracking will enable users to view their historical progress. Users will have access to their tracking both local machines and servers; they may choose to have it accessible from multiple devices, or localized on a single machine. A later version should enable the JSON to be loaded into a database for advanced querying. It should be possible to associate tags with all JSON objects so that disparate objects can be recalled together.

A key UI feature will be the ability to hide and show information. The UI will display the GTD section in a tree where every branch can be expanded or contracted. The user will be able to filter the tree for tags and/or attributes and view a resulting tree containing only items with those tags and attributes. A tag is text that a user has associated with an object, and an attribute is a system property, such as **Calendar** items.

The base code will be written in C++. This leaves open the question of how to implement the UI for presenting the information. There are several options, among them using the cross-platform Qt development tools, using [node.js](https://nodejs.org/en/about/) as an interface between the C++ and a web UI front-end on a server, [exporting the APIs to Python](http://www.boost.org/doc/libs/1_59_0/libs/python/doc/index.html), or [integrating the code into Java](http://www.javaworld.com/article/2077513/learn-java/java-tip-17--integrating-java-with-c--.html). The C++ code will make extensive use of [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) and the [Boost libraries](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)). All code will be written in a cross-platform style, with the possible exception of the UI code. The intent is to host this on Linux, Windows, iOS, and Android.
