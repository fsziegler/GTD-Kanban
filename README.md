Copyright (c) 2015, 2016 Frederick S. Ziegler

#GTD-Kanban ![Screenshot](https://github.com/fsziegler/GTD-Kanban/blob/master/qt/qt_test001/GTD-Kanban.png)

`"I must create a system or be enslaved by another man's; I will not reason and compare: my business is to create."`

`--William Blake`

##1 Life Organizer, based on "Getting Things Done" and Kanban

Purpose: To create a software tool for creative people to organize and track various aspects of their lives, including projects. This is conceptually based on two works: David Allen's book ["Getting Things Done"](https://en.wikipedia.org/wiki/Getting_Things_Done) (**GTD**) and the **Kanban** methodology for managing projects, in particular the form of Kanban outlined in ["Personal Kanban"](http://www.personalkanban.com/) by Jim Benson and Tonianne DeMaria Barry. This tool is intended to empower the individual.

### 1.1 Getting Things Done

One thesis in "Getting Things Done" ("GTD") is that if your mind has more than one problem to solve, you will not be effective at solving any of them until you have put them into a "**trusted system**". This clears your mind to focus on one problem at a time. GTD has a [workflow](https://en.wikipedia.org/wiki/Getting_Things_Done#/media/File:GTDcanonical.png) for processing all of the tasks, ideas, problems, and goals ("issues") in your mind.

A useful open-source brain-storming software tool for initially collecting all these issues is [FreeMind](http://freemind.sourceforge.net/wiki/index.php/Main_Page), which runs on Windows, Mac, and Linux.

####GTD Workflow

`“If money is your hope for independence you will never have it. The only real security that a man will have in this world is a reserve of knowledge, experience, and ability.”`

`--Henry Ford`

In GTD, you start by identifying and classifying all of your issues. You initially create these in your **In-basket** and work through them one by one.

![Screenshot](GTD-Kanban Screenshot - GTD in-basket.png)
*Screenshot showing the GTD in-basket populated with issues.*

If an issue **is not** actionable, you move it into one of the following:
-  your **Someday Maybe** list
-  your **Reference** list
-  **Trash**

at which point you ignore it, at least until some later date.

If an issue **is** actionable, the next question is whether it requires only a single step to complete (a ***task***), or multiple steps (a ***project***). If an issue is a ***task***:
- if it will take "two minutes", then do it now,
- if it will take more time, then either
  - delegate it, in which case move it into your **Waiting for Another Person** list, or
  - defer it, in which case it you either
    - move it into your **Calendar**, to do at a specific time, or
    - move it into your **Next Actions** list, to do as soon as you can.

If an issue is a ***project***, then move it into your **Projects-to-Plan** list. When you do plan your projects, you move the results into your **Project Plans** list and, from here, you identify actionable **tasks** that you will move into your **Next Actions** list. If a project contains many dependencies (i.e. multiple steps are dependent on other steps being completed), then a Gannt chart tool, such as the open-source [GanntProject](http://www.ganttproject.biz/) software tool may be helpful.

Once you have processed your issues, you will have the following lists stored in your **trusted system**:
- your **Someday Maybe** list
- your **Reference** list
- **Trash**
- your **Do It!** list
- your **Waiting for Another Person** list
- tasks in your **Calendar** on specific dates
- your **Next Actions** list
- your **Projects-to-Plan** list
- your **Project Plans** list

Only your **Project Plans** and **Next Actions** lists contain **tasks** to work on at this point.

![Screenshot](GTD-Kanban Screenshot - GTD tree.png)
*Screenshot showing the GTD tree populated with issues organized according to GTD. The GTD in-basket has been minimized to show more of the tree.*

#####Planning Projects
`"Plans are worthless, but planning is everything."`

`--Dwight D. Eisenhower`

How to plan projects in your **Projects-to-Plan** list is beyond the scope of this tool. As a creative person, you probably have your own ways of doing this. Two general approaches are [top-down design and bottom-up design](https://en.wikipedia.org/wiki/Top-down_and_bottom-up_design). A good way to start is to write down your objectives; a more formal way is to follow [Design by Contract](https://en.wikipedia.org/wiki/Design_by_contract) methodology. The GTD-Kanban tool will allow you to link planning files (e.g., documents, spreadsheets, diagrams, URLs, etc.) to any issue. A more in-depth approach to carrying out projects is described in section [1.3 Executing Engineering Projects](#13-executing-engineering-projects).

###1.2 Kanban
`"Strategy without tactics is the slowest route to victory. Tactics without strategy is the noise before defeat."`

`--Sun Tzu`

Your **Project Plans** and **Next Actions** lists are where the GTD-Kanban system will transition from GTD to Kanban. Kanban operates on two principles:
  - **Visualize your work**, and
  - **Limit your work in progress**

In order to **visualize your work**, ***tasks*** are tracked graphically on a **Kanban board**, shown as the green "Kanban Board" window in the lower right of the UI. Generally, ***projects*** are too large to focus on, so you move ***tasks*** first from the **Project Plans** list to the **Next Actions** list, and then onto the **Kanban board**. There are three columns to show the progress of a ***task***:
  - *Ready*
  - *Doing*
  - *Done*

***Tasks*** are depicted in yellow draggable windows. As a task progresses, you move it from one column to the next. Using GTD, you will likely have a large backlog of ***tasks*** and ***projects***. In order to **limit your work in progress**, it is important to identify only a few of these that you can realistically be working on - the authors of "Personal Kanban" recommend starting with three. Move these tasks onto the Kanban board; these will be the rows that cross the *Ready, Doing, Done* columns. This keeps you focused on a manageable subset of ***tasks*** until they are complete *before* starting in on another one. Once you have completed one ***task*** (moved it to *Done*), remove it from the board, and move another one into the *Ready* column.

### 1.3 Executing Engineering Projects
####Make It Work, Make It Right, Make It Fast
`"Make it work, make it right, make it fast."`

`--Kent Beck`

#####Make It Work
First, **make it work** by creating a prototype with end-to-end functionality that proves the concept is viable. This may be buggy and lack many refinements, but it has three advantages:
 - as you approach completion, the risk of not being able to build the product drops dramatically,
 - customers can now visualize and believe in the product, and
 - you have a skeleton of functionality upon which to build.

#####Make It Right
Second, **make it right** by
 - adding all the refinements for a polished product,
 - thoroughly debugging it, and
 - implementing best practices to ensure robustness.

#####Make It Fast
Third, **make it fast** by
 - identifying and eliminating bottlenecks, and 
 - improving or replacing components that do not perform as fast as possible. 

You may iterate through the second and third phases any number of times as your refine your product.

####Reliable, Maintainable, Scalable
`“Build to a standard, not a price.”`

`--Henry E. Steinway`

Endeavour to make your products reliable, maintainable, and scalable. All three of these will result naturally from the following good design practices.

#####Architecture
First, explicitly implement an **architecture** - this is the skeleton in the "make it work" phase. Houses have frames, boats have keels, cars have a chassis or cage, and good software has an architecture. Architecture is a basic structure to which every component is attached in some way. You cannot have a good product with a bad architecture.

#####Modularity
Second, practice **modularity**. A module is a component that has a well-defined purpose and interface, and is reliable. Because a module's scope is limited, its interface should be simple, and it should be straightforward to design a set of tests to validate its functionality. Examples include door assemblies for houses, winches for boats, transmissions for cars, and [objects](https://en.wikipedia.org/wiki/Object-oriented_programming) in software.

Practicing modularity may allow you to identify duplicated functionality, which you should then merge into a single module. This has several benefits:
  - you only have to build and maintain a single module, and
  - if your design changes, 
    - you only have to change a single module, and
    - you cannot make the error of changing the functionality in one place and not in others.

For example, it makes sense to have one design (a module) for both front wheels on a car rather than a separate design for each one.

#####Neat and Clean
Third, keep your work product **neat and clean**. Your desk may be messy, but you should periodically organize and restructure your work tools, factory floor, and code base. Your output, be it machined parts, electronic diagrams, or software should look ready for sale. Better yet, it should have an identifiable "look and feel". All of your code should be well-formatted and follow a uniform coding style.

#####Best Practices
Finally, develop and enforce **best practices**. With experience, technologists discover that certain ways of doing things work really well, and that others are risky. The housing construction, boat-building, automobile, aviation, semiconductor, and other industries all have standards that manufacturers adhere to, and many are written into law and contracts. The software industry is younger and less mature than these other industries, but good standards exist and can prevent hard-to-find bugs. A good example of software design guidelines are the [Basics of the Unix Philosophy](http://www.catb.org/esr/writings/taoup/html/ch01s06.html). An excellent example of coding guidelines can be found in "Effective C++" and other books by [Scott Meyers](http://www.aristeia.com/books.html).

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
  - You are doing some/many/all of the above

Once you have completed a project, if you developed a useful technique (e.g. a flow diagram or standard operating procedure), the tool should allow you to describe and store this. This is often true for legal processes.

Getting an overview may enable you to boil multiple issues down to a single one, resulting in a common solution and moving all these issues forward at once. This is often true when writing software.

You may get satisfaction by keeping a record of the *Done* tasks.

##3. GTD-Kanban Implementation Details
Files created with this tool are stored in the [JSON format](http://www.json.org/). The intent of using JSON is to make the work product as portable and accessible as possible. The JSON format used will allow for one JSON file to reference another. Changes in the tool's JSON work product may be tracked using the Git version control tool, as this supports both local and server based tracking. Such tracking will enable users to view their historical progress. Users will have access to their tracking on both local machines and servers; they may choose to have it accessible from multiple devices, or localized on a single machine. A later version should enable the JSON to be loaded into a database for advanced querying. It should be possible to associate tags with all JSON objects so that disparate objects can be recalled together.

A key UI feature will be the ability to hide and show information in order to focus on specific issues. The UI displays the GTD section in a tree where every branch can be expanded or contracted. The user will be able to filter the tree for tags and/or attributes and view a resulting tree containing only items with those tags and attributes. A tag is text that a user has associated with an object, and an attribute is a system property, such as the time and/or date of **Calendar** items.

The base code is being written in C++. The UI is being developed using the cross-platform Qt development tools, which support Windows, MacOS, Linux, iOS, and Android. Future development may leverage [node.js](https://nodejs.org/en/about/) as an interface between the C++ and a web UI front-end on a server, [export the APIs to Python](http://www.boost.org/doc/libs/1_59_0/libs/python/doc/index.html), or [integrate the code into Java](http://www.javaworld.com/article/2077513/learn-java/java-tip-17--integrating-java-with-c--.html). The C++ code makes extensive use of [STL](https://en.wikipedia.org/wiki/Standard_Template_Library) and the [Boost libraries](https://en.wikipedia.org/wiki/Boost_(C%2B%2B_libraries)). All code is being written in a cross-platform style to support the major desktop, tablet, and smartphone platforms.

You can get a sense of the progress of this project by viewing the [code check-ins](https://github.com/fsziegler/GTD-Kanban/commits/master), which normally have a description.
