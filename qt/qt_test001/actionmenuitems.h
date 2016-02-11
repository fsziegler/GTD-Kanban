#ifndef ACTIONMENUITEMS_H
#define ACTIONMENUITEMS_H

enum EnumAction
{
   kMoveToKanban,
   kMoveUp,
   kMoveDown,
   kMoveToTop,
   kMoveToBottom,
   kSortAscending,
   kSortDescending,
   kDelete,
   kCut,
   kCopy,
   kPaste,
   kLink,
   kMoveUpLevel,
   kExpandAll,
   kCollapseAll,
   kAutoArrange,
};

struct SActionTextPair
{
   EnumAction action;
   QString text;
};

const size_t SActionTextPairLen(16);
const SActionTextPair actionTextPair[SActionTextPairLen] =
{
   { kMoveToKanban, "Move To Kanban" },
   { kMoveUp, "Move Up" },
   { kMoveDown, "Move Down" },
   { kMoveToTop, "Move To Top" },
   { kMoveToBottom, "Move To Bottom" },
   { kSortAscending, "Sort Ascending" },
   { kSortDescending, "Sort Descending" },
   { kDelete, "Delete" },
   { kCut, "Cut" },
   { kCopy, "Copy" },
   { kPaste, "Paste" },
   { kLink, "Link" },
   { kMoveUpLevel, "Move Up Level" },
   { kExpandAll, "Expand All" },
   { kCollapseAll, "Collapse All" },
   { kAutoArrange, "Auto-Arrange" },
};

#endif // ACTIONMENUITEMS_H

