# Developer Log (developer_log.md)

## Text Based RPG Story Tree (Templates + Dynamic Nodes + Shared Children)

---

### Entry 1
**Date:** 2026-04-29  
**Entry Type:** Engineering Decision  
**Task worked on:** Node + Tree skeleton setup (constructor + root pointer plan)  
**Issue or decision:** I needed a simple memory strategy that supports shared children (a node can appear under multiple parents) without double-deleting nodes.  
**Error message / symptom (if applicable):** N/A  
**What I tried:** I considered letting each parent “own” its children, but that would cause double free if two parents share the same child pointer.  
**Fix / resolution (or final decision):** I chose a simple ownership rule: the Tree keeps a list of every dynamically allocated node in a single container, so the destructor can delete each node exactly once. Parents only store child pointers (non-owning).  
**Commit(s):** `implement Node constructor and Tree initialization`
---
### Entry 2
**Date:** 2026-04-29  
**Entry Type:** Engineering Decision  
**Task worked on:** Project setup + developer log started  
**Issue or decision:** The submission requires a developer log that matches commits, so I set it up immediately to avoid forgetting later.  
**Error message / symptom (if applicable):** N/A  
**What I tried:** I started with a blank file but realized I needed the required format and headings so I wouldn’t rewrite later.  
**Fix / resolution (or final decision):** Added a log template and made sure the repo structure is ready for regular commits.  
**Commit(s):** `setup project and add developer_log template`
---
### Entry 3
**Date:** 2026-05-01  
**Entry Type:** Bug Fix Entry  
**Task worked on:** `createRoot` with dynamic allocation  
**Issue or decision:** The tree needs a real root node stored dynamically. Also, it should ignore repeated root creation attempts to prevent leaks.  
**Error message / symptom (if applicable):** Before this commit, the tree didn’t actually create any nodes, so printing/testing didn’t show anything meaningful.  
**What I tried:** I tested calling `createRoot()` twice and thought about whether to overwrite or ignore it.  
**Fix / resolution (or final decision):** Implemented `createRoot()` using `new`, stored the root pointer, and pushed the root into `allNodes` so it’s tracked for deletion later. If root already exists, it prints a message and ignores the call.  
**Commit(s):** `implement createRoot with dynamic allocation`
---
### Entry 4
**Date:** 2026-05-02  
**Entry Type:** Bug Fix Entry  
**Task worked on:** `findNode` lookup  
**Issue or decision:** `addNode()` depends on finding the parent first, so I needed a working way to look up nodes by ID.  
**Error message / symptom (if applicable):** Parent linking couldn’t work because “Parent not found” would happen every time unless I manually kept a pointer.  
**What I tried:** I thought about doing recursive DFS search, but since I already track all allocated nodes in `allNodes`, I tried a simple loop search first.  
**Fix / resolution (or final decision):** Implemented `findNode(id)` by iterating through `allNodes` and returning the matching pointer or `nullptr`. This was simpler and worked well for the assignment size.  
**Commit(s):** `implement findNode lookup`
---
### Entry 5
**Date:** 2026-05-04  
**Entry Type:** Bug Fix Entry  
**Task worked on:** Basic `addNode` parent → child linking  
**Issue or decision:** I needed `addNode(parentID, childID, value)` to (1) find the parent, (2) create or reuse the child node, and (3) link the pointers.  
**Error message / symptom (if applicable):** If the parent ID didn’t exist yet, linking would crash or do nothing useful.  
**What I tried:** I started by always creating a new child node, but that didn’t support “shared children” correctly.  
**Fix / resolution (or final decision):** Implemented `addNode()` to safely check for missing root, empty child ID, and missing parent. If parent exists, it links the child pointer into the parent’s `children` list.  
**Commit(s):** `implement addNode basic parent-child linking`
---
### Entry 6
**Date:** 2026-05-04  
**Entry Type:** Bug Fix / Edge Case / Testing Entry  
**Task worked on:** Prevent duplicate child links + support shared children  
**Issue or decision:** The story format allows the same child ID to appear under multiple parents. Also, it’s possible to accidentally link the same child twice under one parent if addNode is called multiple times.  
**Error message / symptom (if applicable):** I saw repeated “Child -> X” lines under the same node, and I realized I was duplicating links. Also, creating a new node every time caused multiple nodes with the same ID.  
**What I tried:** I tested a small manual setup where Node 3 and Node 2 both link to Node 4. I also purposely called addNode twice with the same parent/child.  
**Fix / resolution (or final decision):** Added a “get or create” style approach so each ID maps to a single Node pointer, and added a duplicate check inside the parent’s child list before pushing. This keeps shared nodes possible but avoids duplicate edges.  
**Commit(s):** `prevent duplicate child links and support shared children`
---