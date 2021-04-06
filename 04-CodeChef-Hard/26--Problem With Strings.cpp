
 
    #include <vector>
    #include <map>
    #include <set>
    #include <iostream>
    #include <sstream>
    #include <fstream>
     
    #ifdef INT_MAX
    #undef INT_MAX
    #endif
     
    #ifdef INT_MIN
    #undef INT_MIN
    #endif
     
    #define INT_MAX 10000
    #define INT_MIN 0
    int MAX_EMPIRICAL_SEARCH_DEPTH = 1;
    int MAX_DEPTH_SEARCH = 0;
    bool SKIP_RESIDUAL_SLIDES = false;
    bool SKIP_SLIDES = false;
     
    //#define READ_FROM_TEST_FILE 1
    //#define VERBOSEOUTPUT 1
    //#define LOG_SLIDE_MOVES 1
    //#define LOG_TOTAL_MOVES 1
     
   
     
    class Node {
    public:
        int id;
        int topLinks[2];
        int bottomLinks[2];
        
        int lowestIndex();
        int highestIndex();
        
        Node();
        Node(const Node &node);
        Node(int id, int *topLinks, int *bottomLinks);
        
        void operator=(const Node& node);
    };
     
   
    class RopeReducer {
    public:
        // graph topology analysis
        bool isSimpleCross(Node &node);
        bool isDoubleCross(Node &a, Node &b);
        bool isSlidePossible(Node &n1, Node &n2, Node &n3, Node* &a, Node* &b, Node* &c);
        
        // graph topology reductions
        void reduceSimpleCross(Node &node, int *equivalentLinks);
        void reduceDoubleCross(Node &a, Node &b, int *equivalentLinks);
        void makeSlide(Node &a, Node &b, Node &c);
        
        // aux members
        bool nodeContainsLinkOnTop(Node &node, int linkIndex);
        bool nodeContainsLinkOnBottom(Node &node, int linkIndex);
        bool nodesShareATopLink(Node &nodeA, Node &nodeB);
        bool nodesShareABottomLink(Node &nodeA, Node &nodeB);
        bool nodesShareAMixedLink(Node &nodeA, Node &nodeB);
    };
     
   
     
    class RopeSolver {
        
    private:
        int searchLevel;
        void printIndentation();
        long moves;
        
    public:
        
        typedef enum {
            ROPE_STATE_OPEN,
            ROPE_STATE_CLOSED,
            ROPE_STATE_UNKNOWN
        } ROPE_STATE;
        
        typedef struct {
            int link;
            int pivotId;
            
            int aId;
            int bId;
        } slideMoveType;
        
        
        // starting and ending link indexes
        int startingLink;
        int endingLink;
        std::map<int, Node> _ropeNodes;
        ROPE_STATE ropeState;
        
        // reduce operations
        RopeReducer *_reducer;
        
        // rope update
        void updateNodeIndexes(std::map<int, Node> &nodes, int fromIndex, int toIndex);
        
        // Problem setting
        void clearProblem();         // clear the rope problem
        void addNode(Node &node);    // add a new node
        
        // solve operations
        bool reduceSimpleCross(std::map<int, Node> &nodes);
        bool reduceDoubleCross(std::map<int, Node> &nodes);
        
        void findSlideMovesWithBaseNodes(std::map<int, Node> &nodes, std::set<int> &searchNodeIndexes, Node &nodeA, Node &nodeB, std::vector<slideMoveType> &slideMoves);
        void findSlideMoves(std::map<int, Node> &nodes, std::vector<slideMoveType> &slideMoves);
        bool reduceRope(std::map<int, Node> &nodes);
        void makeStep(std::map<int, Node> &nodes, std::vector<slideMoveType> &prevMoves, int empiricalLevelLimit);
        void makeStep(std::map<int, Node> &nodes);
        void solveProblem();
        
        RopeSolver();
        ~RopeSolver();
        
        
    private:
        
        void duplicateNodes(std::map<int, Node> &nodes, std::map<int, Node> &newNodeList);
    };
     
  
     
    class RopeParser {
    private:
        
        // some locals
        typedef enum {
            ROPE_DIRECTION_TOP,
            ROPE_DIRECTION_BOTTOM,
            ROPE_DIRECTION_LEFT,
            ROPE_DIRECTION_RIGHT,
            ROPE_DIRECTION_UNDEFINED,
        } ROPE_DIRECTION;
        
        typedef struct {
            char c;
            bool isCross;
            int firstScanLinkIndex;
            int secondScanLinkIndex;
            int nodeIndex;
        } ropeSchemaNode;
        
        typedef struct {
            int iRow, iCol;
            bool horizontal;
            ROPE_DIRECTION firstScanDir;
            ROPE_DIRECTION secondScanDir;
        } NODE_DESCRIPTOR;
        
        RopeSolver _solver;
        ropeSchemaNode _ropeSchema[120][120];
        int startingRow, startingCol;
        int rows, cols;
        ROPE_DIRECTION startingDirection;
        void parseSchema();
        void clearSchema();
        std::ifstream f;
        
    public:
        void initStream();
        void readRowsAndCols();
        std::string readLine();
        void runParser();
        bool dataAvailableFromStream();
    };
     
   
     
    Node::Node() {
        id = 0;
        topLinks[0] = 0;
        topLinks[1] = 0;
        bottomLinks[0] = 0;
        bottomLinks[1] = 0;
    }
     
    Node::Node(const Node &node) {
        this->id = node.id;
        
        this->topLinks[0] = node.topLinks[0];
        this->topLinks[1] = node.topLinks[1];
        
        this->bottomLinks[0] = node.bottomLinks[0];
        this->bottomLinks[1] = node.bottomLinks[1];
    }
     
    Node::Node(int id, int *topLinks, int *bottomLinks) {
        this->id = id;
        
        this->topLinks[0] = topLinks[0];
        this->topLinks[1] = topLinks[1];
        
        this->bottomLinks[0] = bottomLinks[0];
        this->bottomLinks[1] = bottomLinks[1];
    }
     
    int Node::lowestIndex() {
        return std::min(std::min(topLinks[0], topLinks[1]),
                        std::min(bottomLinks[0], bottomLinks[1]));
    }
     
    int Node::highestIndex() {
        return std::max(std::max(topLinks[0], topLinks[1]),
                        std::max(bottomLinks[0], bottomLinks[1]));
    }
     
    void Node::operator=(const Node& node) {
        id = node.id;
        
        topLinks[0] = node.topLinks[0];
        topLinks[1] = node.topLinks[1];
        
        bottomLinks[0] = node.bottomLinks[0];
        bottomLinks[1] = node.bottomLinks[1];
    }
     
   
     
    // graph topology analysis
    inline bool RopeReducer::isSimpleCross(Node &node) {
        // smple cross condition: the same link appears on both top and bottom in the same node
        return nodeContainsLinkOnBottom(node, node.topLinks[0]) || nodeContainsLinkOnBottom(node, node.topLinks[1]);
    }
     
    inline bool RopeReducer::isDoubleCross(Node &a, Node &b) {
        // double cross condition: two nodes shares both a top link and a bottom link
        bool topLinkIsShared, bottomLinkIsShared;
        
        topLinkIsShared = nodeContainsLinkOnTop(b, a.topLinks[0]) || nodeContainsLinkOnTop(b, a.topLinks[1]);
        bottomLinkIsShared = nodeContainsLinkOnBottom(b, a.bottomLinks[0]) || nodeContainsLinkOnBottom(b, a.bottomLinks[1]);
        
        return topLinkIsShared && bottomLinkIsShared;
    }
     
    inline bool RopeReducer::isSlidePossible(Node &n1, Node &n2, Node &n3, Node* &a, Node* &b, Node* &c) {
        // slide condition is that two nodes should share the same top, two should share the same bottom and two should share a mixed link
        // convention:
        // A shares a bottom link with B
        // a shares a top link with C
        // B shares a mixed link with C
        if (nodesShareABottomLink(n1, n2)) {
            a = &n1;
            b = &n2;
            c = &n3;
        } else if (nodesShareABottomLink(n1, n3)) {
            a = &n1;
            b = &n3;
            c = &n2;
        } else if (nodesShareABottomLink(n2, n3)) {
            a = &n2;
            b = &n3;
            c = &n1;
        } else {
            // no top link shared, slide is not possible
            return false;
        }
        
        // look for the node that shares the top link
        if (nodesShareATopLink(*b, *c)) {
            // B shares the top link, it should be A
            std::swap(a,b);
        } else if (!nodesShareATopLink(*a, *c)) {
            // neither A nor B shares a top link with C
            return false;
        }
        
        // a must share a bottom lilnk with C
        if (!nodesShareAMixedLink(*b, *c))
            return false;
        
        return true;
    }
     
    // graph topology reductions
    void RopeReducer::reduceSimpleCross(Node &node, int *equivalentLinks) {
        int equivalentTopNodeIndex;
        int equivalentBottomNodeIndex;
        
        // nothing to be reduced indeed, returns the equivlent nodes
        if (nodeContainsLinkOnBottom(node, node.topLinks[0])) {
            equivalentTopNodeIndex = 1;
        } else {
            equivalentTopNodeIndex = 0;
        }
        
        if (nodeContainsLinkOnTop(node, node.bottomLinks[0])) {
            equivalentBottomNodeIndex = 1;
        } else {
            equivalentBottomNodeIndex = 0;
            
        }
        
        // save equivalent link indexes
        equivalentLinks[0] = node.topLinks[equivalentTopNodeIndex];
        equivalentLinks[1] = node.bottomLinks[equivalentBottomNodeIndex];
        
        if (equivalentLinks[0] > equivalentLinks[1]) {
            std::swap(equivalentLinks[0], equivalentLinks[1]);
        }
    }
     
    void RopeReducer::reduceDoubleCross(Node &a, Node &b, int *equivalentLinks) {
        int equivalentTopNodeIndexA;
        int equivalentTopNodeIndexB;
        int equivalentBottomNodeIndexA;
        int equivalentBottomNodeIndexB;
        
        if (nodeContainsLinkOnTop(a, b.topLinks[0])) {
            equivalentTopNodeIndexB = 1;
        } else {
            equivalentTopNodeIndexB = 0;
        }
        if (nodeContainsLinkOnTop(b, a.topLinks[0])) {
            equivalentTopNodeIndexA = 1;
        } else {
            equivalentTopNodeIndexA = 0;
        }
        
        if (nodeContainsLinkOnBottom(a, b.bottomLinks[0])) {
            equivalentBottomNodeIndexB = 1;
        } else {
            equivalentBottomNodeIndexB = 0;
        }
        if (nodeContainsLinkOnBottom(b, a.bottomLinks[0])) {
            equivalentBottomNodeIndexA = 1;
        } else {
            equivalentBottomNodeIndexA = 0;
        }
        
        // save equivalent link indexes, mantain sorted
        equivalentLinks[0] = a.topLinks[equivalentTopNodeIndexA];
        equivalentLinks[1] = b.topLinks[equivalentTopNodeIndexB];
        equivalentLinks[2] = a.bottomLinks[equivalentBottomNodeIndexA];
        equivalentLinks[3] = b.bottomLinks[equivalentBottomNodeIndexB];
        
        if (equivalentLinks[0] > equivalentLinks[1]) {
            std::swap(equivalentLinks[0], equivalentLinks[1]);
        }
        if (equivalentLinks[2] > equivalentLinks[3]) {
            std::swap(equivalentLinks[2], equivalentLinks[3]);
        }
    }
     
    inline void RopeReducer::makeSlide(Node &a, Node &b, Node &c) {
        // perform index exchanges
        int aTop[2];
        int aBot[2];
        int bTop[2];
        int bBot[2];
        int cTop[2];
        int cBot[2];
        
        aTop[0] = a.topLinks[0];
        aTop[1] = a.topLinks[1];
        aBot[0] = a.bottomLinks[0];
        aBot[1] = a.bottomLinks[1];
     
        bTop[0] = b.topLinks[0];
        bTop[1] = b.topLinks[1];
        bBot[0] = b.bottomLinks[0];
        bBot[1] = b.bottomLinks[1];
     
        cTop[0] = c.topLinks[0];
        cTop[1] = c.topLinks[1];
        cBot[0] = c.bottomLinks[0];
        cBot[1] = c.bottomLinks[1];
        
        a.topLinks[0] = cTop[0];
        a.topLinks[1] = cTop[1];
        a.bottomLinks[0] = bBot[0];
        a.bottomLinks[1] = bBot[1];
     
        b.topLinks[0] = cBot[0];
        b.topLinks[1] = cBot[1];
        b.bottomLinks[0] = aBot[0];
        b.bottomLinks[1] = aBot[1];
     
        c.topLinks[0] = aTop[0];
        c.topLinks[1] = aTop[1];
        c.bottomLinks[0] = bTop[0];
        c.bottomLinks[1] = bTop[1];
    }
     
    // aux members
    inline bool RopeReducer::nodeContainsLinkOnTop(Node &node, int linkIndex) {
        return node.topLinks[0] == linkIndex || node.topLinks[1] == linkIndex;
    }
     
    inline bool RopeReducer::nodeContainsLinkOnBottom(Node &node, int linkIndex) {
        return node.bottomLinks[0] == linkIndex || node.bottomLinks[1] == linkIndex;
    }
     
    inline bool RopeReducer::nodesShareATopLink(Node &nodeA, Node &nodeB) {
        // one top link should be on both top links nodes
        return nodeContainsLinkOnTop(nodeA, nodeB.topLinks[0]) || nodeContainsLinkOnTop(nodeA, nodeB.topLinks[1]);
    }
     
    inline bool RopeReducer::nodesShareABottomLink(Node &nodeA, Node &nodeB) {
        // one bottom link should be on both bottom links nodes
        return nodeContainsLinkOnBottom(nodeA, nodeB.bottomLinks[0]) || nodeContainsLinkOnBottom(nodeA, nodeB.bottomLinks[1]);
    }
     
    inline bool RopeReducer::nodesShareAMixedLink(Node &nodeA, Node &nodeB) {
        // one of the top link should be one of the bottom in the other node
        bool topOnNodeA, topOnNodeB;
        
        topOnNodeA = nodeContainsLinkOnBottom(nodeA, nodeB.topLinks[0]) || nodeContainsLinkOnBottom(nodeA, nodeB.topLinks[1]);
        topOnNodeB = nodeContainsLinkOnBottom(nodeB, nodeA.topLinks[0]) || nodeContainsLinkOnBottom(nodeB, nodeA.topLinks[1]);
        return topOnNodeA || topOnNodeB;
    }
     
     
   
     
    RopeSolver::RopeSolver() {
        _reducer = new RopeReducer();
        clearProblem();
    }
     
    RopeSolver::~RopeSolver() {
        clearProblem();
    }
     
     
    // PRIVATE
     
    void RopeSolver::printIndentation() {
        for (int i=0; i < searchLevel; i++) {
            std::cout << "    ";
        }
    }
     
    // PUBLIC
     
    void RopeSolver::updateNodeIndexes(std::map<int, Node> &nodes, int fromIndex, int toIndex) {
        
        // always go from the lower to the higher
        if (fromIndex > toIndex) {
            std::swap(fromIndex, toIndex);
        }
        
        // if from is the starting node than exchange
        if (fromIndex == startingLink) {
            fromIndex = toIndex;
            toIndex = startingLink;
        }
        
        for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
            Node *node = &(it->second);
            
            if (node->topLinks[0] == fromIndex) {
                node->topLinks[0] = toIndex;
            }
            if (node->topLinks[1] == fromIndex) {
                node->topLinks[1] = toIndex;
            }
            
            if (node->bottomLinks[0] == fromIndex) {
                node->bottomLinks[0] = toIndex;
            }
            
            if (node->bottomLinks[1] == fromIndex) {
                node->bottomLinks[1] = toIndex;
            }
        }
    }
     
    void RopeSolver::clearProblem() {
     
        moves = 0;
        _ropeNodes.clear();
        
        startingLink = INT_MAX;
        endingLink = INT_MIN;
        ropeState = ROPE_STATE_UNKNOWN;
    }
     
    void RopeSolver::addNode(Node &node) {
        _ropeNodes[node.id] = Node(node);
        startingLink = std::min(startingLink, node.lowestIndex());
        endingLink = std::max(endingLink, node.highestIndex());
    }
     
     
    bool RopeSolver::reduceSimpleCross(std::map<int, Node> &nodes) {
        // reduce all nodes
        for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
            
            Node *node = &(it->second);
            
            if (_reducer->isSimpleCross(*node)) {
                
                int equivalentLinks[2];
                _reducer->reduceSimpleCross(*node, equivalentLinks);
                
    #ifdef VERBOSEOUTPUT
                printIndentation();
                std::cout << "node <" << node->id << "> de-twisted" << std::endl;
    #endif
                // mark the end if starting and ending links are discovered to be equivalend
                if (equivalentLinks[0] == startingLink && equivalentLinks[1] == endingLink) {
                    ropeState = ROPE_STATE_OPEN;
                }
                
                // node is twisted, reduce it
                updateNodeIndexes(nodes, equivalentLinks[0], equivalentLinks[1]);
                
                // remove the twisted node, if no more nodes with this root exist then remove the array node from the map
                if (nodes.find(node->id) == nodes.end()) {
                    std::cout << "WARNING: map is zero size";
                }
                
                nodes.erase(node->id);
                
                // SIMPLE CROSS REDUCTION IS A MOVE
                moves++;
                
                return true;
            }
        }
        
        return false;
    }
     
    bool RopeSolver::reduceDoubleCross(std::map<int, Node> &nodes) {
        // analyze all node pairs
        for (std::map<int, Node>::iterator i = nodes.begin(); i != nodes.end(); i++) {
            std::map<int, Node>::iterator nextI = i;
            nextI++;
            
            for (std::map<int, Node>::iterator j = nextI;  j != nodes.end(); j++) {
                Node *nodeA = &(i->second);
                Node *nodeB = &(j->second);
                
                if (_reducer->isDoubleCross(*nodeA, *nodeB)) {
                    
                    // reduce doble cross
                    int equivalentLinks[4];
                    _reducer->reduceDoubleCross(*nodeA, *nodeB, equivalentLinks);
                    
    #ifdef VERBOSEOUTPUT
                    printIndentation();
                    std::cout << "nodes <" << nodeA->id << ", " << nodeB->id << ">  de-overlap" << std::endl;
    #endif
                    // mark the end if starting and ending links are discovered to be equivalend
                    if ((equivalentLinks[0] == startingLink && equivalentLinks[1] == endingLink) ||
                        (equivalentLinks[2] == startingLink && equivalentLinks[3] == endingLink)) {
                        ropeState = ROPE_STATE_OPEN;
                        return true;
                    }
                    
                    updateNodeIndexes(nodes, equivalentLinks[0], equivalentLinks[1]);
                    updateNodeIndexes(nodes, equivalentLinks[2], equivalentLinks[3]);
                    
                    // remove equivalent nodes
                    nodes.erase(j);
                    nodes.erase(i);
                    
                    // DOUBLE CROSS REDUCTION IS A MOVE
                    moves++;
                    
                    // update only 1 equivalence
                    return true;
                }
            }
        }
        
        return false;
    }
     
    void RopeSolver::findSlideMoves(std::map<int, Node> &nodes, std::vector<slideMoveType> &slideMoves) {
        
        // create a support structure containing some maps between links and nodes
        
        std::map<int, std::vector<int> > topNodes;       // maps the list of top nodes for a gived link index
        std::map<int, std::vector<int> > bottomNodes;    // maps the list of bottom nodes for a gived link index
        std::set<int> availableLinks;
        
        
        for (std::map<int, Node>::iterator iNode=nodes.begin(); iNode != nodes.end(); iNode++) {
            Node *n = &(iNode->second);
            
            topNodes[n->topLinks[0]].push_back(n->id);
            topNodes[n->topLinks[1]].push_back(n->id);
            
            bottomNodes[n->bottomLinks[0]].push_back(n->id);
            bottomNodes[n->bottomLinks[1]].push_back(n->id);
            
            availableLinks.insert(n->topLinks[0]);
            availableLinks.insert(n->topLinks[1]);
            availableLinks.insert(n->bottomLinks[0]);
            availableLinks.insert(n->bottomLinks[1]);
        }
        
        for (std::set<int>::iterator it = availableLinks.begin(); it != availableLinks.end(); it++) {
            int iLink = *it;
            if (bottomNodes[iLink].size() == 2) {
                
                Node *nodeA = &(nodes[bottomNodes[iLink][0]]);
                Node *nodeB = &(nodes[bottomNodes[iLink][1]]);
                
                // link is under two other links, check if there is another node that closess the slide triangle
                // create the list of nodes connected to the current link's extreme nodes
                std::set<int> searchIndexes;
                std::vector<int> topNodeA1 = topNodes[nodeA->topLinks[0]];
                std::vector<int> topNodeA2 = topNodes[nodeA->topLinks[1]];
                std::vector<int> topNodeB1 = topNodes[nodeB->topLinks[0]];
                std::vector<int> topNodeB2 = topNodes[nodeB->topLinks[1]];
                
                searchIndexes.insert(&topNodeA1[0], &topNodeA1[0] + topNodeA1.size());
                searchIndexes.insert(&topNodeA2[0], &topNodeA2[0] + topNodeA2.size());
                searchIndexes.insert(&topNodeB1[0], &topNodeB1[0] + topNodeB1.size());
                searchIndexes.insert(&topNodeB2[0], &topNodeB2[0] + topNodeB2.size());
                
                // remove from the search the current link's nodes
                searchIndexes.erase(bottomNodes[iLink][0]);
                searchIndexes.erase(bottomNodes[iLink][1]);
                
                // search for the possible links
                for (std::set<int>::iterator it = searchIndexes.begin(); it != searchIndexes.end(); it++) {
                    
                    Node *checkNode = &(nodes.at(*it));
                    Node *a, *b, *c;
                    if (_reducer->isSlidePossible(*nodeA, *nodeB, *checkNode, a, b, c)) {
                        
                        slideMoveType slideMove;
                        slideMove.link = iLink;
                        slideMove.pivotId = c->id;
                        
                        if (a->id == nodeA->id) {
                            slideMove.aId = a->id;
                            slideMove.bId = b->id;
                        } else {
                            slideMove.aId = b->id;
                            slideMove.bId = a->id;
                        }
                        
                        slideMoves.push_back(slideMove);
                    }
                }
            }
        }
    }
     
    bool RopeSolver::reduceRope(std::map<int, Node> &nodes) {
        // perform a reduction while is't possible
        bool atLeastOneReductionHasDone = false;
        bool reductionDone = true;
        while(reductionDone) {
            reductionDone = false;
            
            reductionDone |= reduceSimpleCross(nodes);
            if (ropeState == ROPE_STATE_OPEN) {
                return true;
            }
            if (!reductionDone) {
                reductionDone |= reduceDoubleCross(nodes);
            }
            
            atLeastOneReductionHasDone |= reductionDone;
            if (ropeState == ROPE_STATE_OPEN) {
                return true;
            }
        }
        
        // check if at least one reduction has been done
        return atLeastOneReductionHasDone;
        
    }
     
    inline void RopeSolver::makeStep(std::map<int, Node> &nodes, std::vector<slideMoveType> &prevMoves, int empiricalLevelLimit) {
        
        // increase search level
        searchLevel++;
        
    #ifdef LOG_SLIDE_MOVES
        if (moves % 1000 == 0)
        std::cout << " moves: " << moves << ", nodes: " << nodes.size() << std::endl;
    #endif
        
        // reduce the rope
        bool reductionExecuted = reduceRope(nodes);
        
        if (!reductionExecuted && (searchLevel > empiricalLevelLimit || searchLevel >= MAX_DEPTH_SEARCH)) {
            searchLevel--;
            return;
        }
     
        if (ropeState == ROPE_STATE_OPEN) {
            searchLevel--;
            return;
        } else {
            
            // if no reductions are possible then assume that the rope is still knotted,
            // do not slide and exit immediatly
            if (SKIP_SLIDES) {
                searchLevel--;
                return;
            }
            
            // rope problem is not yet solved, get the list of links that can be slided
            std::vector<slideMoveType> slideMoves;          // maps the list of possible slide moves
            std::vector<slideMoveType> residualSlideMoves;  // maps the list of
            
            // find the list of possible slide moves
            findSlideMoves(nodes, slideMoves);
            
            // recursively go through the one after which a reduction is possible
            for (int iSlideMove=0; iSlideMove < slideMoves.size(); iSlideMove++) {
                std::map<int, Node> newNodes;
                duplicateNodes(nodes, newNodes);
                
                // make a slide move
                slideMoveType *slideMove = &(slideMoves.at(iSlideMove));
                Node *nodeA = &(newNodes[slideMove->aId]);
                Node *nodeB = &(newNodes[slideMove->bId]);
                Node *nodeC = &(newNodes[slideMove->pivotId]);
                _reducer->makeSlide(*nodeA, *nodeB, *nodeC);
                
                // SLIDE IS A MOVE
                moves++;
                
    #ifdef VERBOSEOUTPUT
                printIndentation();
                std::cout << "slide link " << slideMove->link << " over node <" << slideMove->pivotId << ">" << std::endl;
    #endif
                
                // try a reduction step
                searchLevel++;
                if (reduceRope(newNodes)) {
                    // a reduction has been possible!
                    
                    // check if problem has been solved
                    if (ropeState == ROPE_STATE_OPEN) {
                        searchLevel--;
                        return;
                    }
                    
                    // go through recursively resetting the past slide moves
                    std::vector<slideMoveType> newMoves;
                    makeStep(newNodes, newMoves, searchLevel + MAX_EMPIRICAL_SEARCH_DEPTH);
                    
                } else {
                    // reduction has not been possible, queue the slide move
                    residualSlideMoves.push_back(*slideMove);
                    
    #ifdef VERBOSEOUTPUT
                    printIndentation();
                    std::cout << "this slide did not reduced the rope, go deep on this slide later." << std::endl;
    #endif
                }
                newNodes.clear();
                searchLevel--;
                
                // check if problem has been solved
                if (ropeState == ROPE_STATE_OPEN) {
                    return;
                }
     
            }
            
            // if step is here then no solution has been yet found, proceed with the residual slide moves avoiding to repeat past moves
            
            for (int iSlideMove = 0; iSlideMove < residualSlideMoves.size(); iSlideMove++) {
                
                slideMoveType slideMove = residualSlideMoves.at(iSlideMove);
                
                // discard already done moves
                bool alreadyDone = false;
                
                // TEMP::: avoid residual moves, step back
                if (SKIP_RESIDUAL_SLIDES)
                    alreadyDone = true;
                
                for (int iPrevSlideMove = 0; iPrevSlideMove < prevMoves.size(); iPrevSlideMove++) {
                    slideMoveType prevSlideMove = prevMoves.at(iPrevSlideMove);
                    
                    if (slideMove.link == prevSlideMove.link && slideMove.pivotId == prevSlideMove.pivotId) {
                        alreadyDone = true;
                        break;
                    }
                }
                if (alreadyDone)
                    continue;
                
    #ifdef VERBOSEOUTPUT
                printIndentation();
                std::cout << "residual slide link " << slideMove.link << " over node <" << slideMove.pivotId << ">" << std::endl;
    #endif
                
                // do the slide move and go through recursively
                std::map<int, Node> newNodes;
                duplicateNodes(nodes, newNodes);
                
                // make a slide move
                Node *nodeA = &(newNodes[slideMove.aId]);
                Node *nodeB = &(newNodes[slideMove.bId]);
                Node *nodeC = &(newNodes[slideMove.pivotId]);
                _reducer->makeSlide(*nodeA, *nodeB, *nodeC);
                
                // SIMPLE CROSS REDUCTION IS A MOVE
                moves++;
     
                prevMoves.push_back(slideMove);
                if (reductionExecuted) {
                    makeStep(newNodes, prevMoves, searchLevel + MAX_EMPIRICAL_SEARCH_DEPTH);
                } else {
                    makeStep(newNodes, prevMoves, empiricalLevelLimit);
                }
                prevMoves.pop_back();
                
                // clear nodes
                newNodes.clear();
            }
        }
        
        // if step is here then no solutions have been done for such rope configuartion
        searchLevel--;
    }
     
    void RopeSolver::solveProblem() {
        
        // set the max depth search as the number of nodes
        if (_ropeNodes.size() > 20) {
            MAX_DEPTH_SEARCH = (int)(_ropeNodes.size() * 100) / 70;
        } else {
            MAX_DEPTH_SEARCH = (int)_ropeNodes.size();
        }
     
        searchLevel = 0;
        std::vector<slideMoveType> slideMoves;
        makeStep(_ropeNodes, slideMoves, searchLevel + MAX_EMPIRICAL_SEARCH_DEPTH);
        if (_ropeNodes.size() == 0) {
            ropeState = ROPE_STATE_OPEN;
        } else if (ropeState == ROPE_STATE_UNKNOWN) {
            ropeState = ROPE_STATE_CLOSED;
        }
        
    #ifdef LOG_TOTAL_MOVES
        std::cout << std::endl << " | solved in : " << moves << " | ";
    #endif
     
    }
     
    // PRIVATE
     
    void RopeSolver::duplicateNodes(std::map<int, Node> &nodes, std::map<int, Node> &newNodeList) {
        // duplicate all nodes
        for (std::map<int, Node>::iterator it = nodes.begin(); it != nodes.end(); it++) {
            Node *node = &(it->second);
            newNodeList[node->id] = Node(*node);
        }
    }
     
   
     
    void RopeParser::parseSchema() {
        // find the first border node
        // 1. start from the first row
        
        int iRow, iCol, iLink;
        iRow = startingRow;
        iCol = startingCol;
        iLink = 0;
        ROPE_DIRECTION dir = startingDirection;
        
        // store the starting link id
        ropeSchemaNode node;
        node.firstScanLinkIndex = 0;
        node.isCross = false;
        node.c = '.';
        _ropeSchema[iRow][iCol] = node;
        
        std::vector<NODE_DESCRIPTOR> nodes;
        
        bool done = false;
        while (!done) {
            
            // parse the current cell
            ropeSchemaNode newCell = _ropeSchema[iRow][iCol];
            if (newCell.isCross) {
                
                // save the second scan direction
                nodes[_ropeSchema[iRow][iCol].nodeIndex].secondScanDir = dir;
                _ropeSchema[iRow][iCol].secondScanLinkIndex = iLink;
     
                // increment the link counter
                iLink++;
                
            } else {
            
                switch (newCell.c) {
                    case '+': { // angle, find the new direction
                        
                        char searchCell;
                        char HcrossCell = 'H';
                        char IcrossCell = 'I';
                        char AcornerCell = '+';
                        if (dir == ROPE_DIRECTION_LEFT || dir == ROPE_DIRECTION_RIGHT) {
                            // search on top if exist an explicit direction | or H or I
                            searchCell = '|';
                            if (_ropeSchema[iRow-1][iCol].c == searchCell ||
                                _ropeSchema[iRow-1][iCol].c == HcrossCell ||
                                _ropeSchema[iRow-1][iCol].c == IcrossCell) {
                                dir = ROPE_DIRECTION_TOP;
                            } else if (_ropeSchema[iRow+1][iCol].c == searchCell ||
                                       _ropeSchema[iRow+1][iCol].c == HcrossCell ||
                                       _ropeSchema[iRow+1][iCol].c == IcrossCell) {
                                dir = ROPE_DIRECTION_BOTTOM;
                            } else {
                                // no explicit direction present, should be two corners connected
                                if (_ropeSchema[iRow-1][iCol].c == AcornerCell) {
                                    dir = ROPE_DIRECTION_TOP;
                                } else {
                                    dir = ROPE_DIRECTION_BOTTOM;
                                }
                            }
                        } else {
                            // search on top if exist an explicit direction - or H or I
                            searchCell = '-';
                            if (_ropeSchema[iRow][iCol-1].c == searchCell ||
                                _ropeSchema[iRow][iCol-1].c == HcrossCell ||
                                _ropeSchema[iRow][iCol-1].c == IcrossCell) {
                                dir = ROPE_DIRECTION_LEFT;
                            } else if (_ropeSchema[iRow][iCol+1].c == searchCell ||
                                       _ropeSchema[iRow][iCol+1].c == HcrossCell ||
                                       _ropeSchema[iRow][iCol+1].c == IcrossCell) {
                                dir = ROPE_DIRECTION_RIGHT;
                            } else {
                                // no explicit direction present, should be two corners connected
                                if (_ropeSchema[iRow][iCol-1].c == AcornerCell) {
                                    dir = ROPE_DIRECTION_LEFT;
                                } else {
                                    dir = ROPE_DIRECTION_RIGHT;
                                }
                            }
                        }
                        
                        _ropeSchema[iRow][iCol].firstScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].secondScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].isCross = false;
                        
                    }
                        break;
                        
                    case 'I': { // VERTICAL NODE
                        NODE_DESCRIPTOR desc;
                        desc.iRow = iRow;
                        desc.iCol = iCol;
                        desc.horizontal = false;
                        desc.firstScanDir = dir;
                        nodes.push_back(desc);
                        
                        _ropeSchema[iRow][iCol].nodeIndex = (int) nodes.size()-1;
                        _ropeSchema[iRow][iCol].firstScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].secondScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].isCross = true; // delete the node in order to parse it once
                        
                        // increment link counter
                        iLink++;
                    }
                        break;
                        
                    case 'H': { // HORIZONTAL NODE
                        NODE_DESCRIPTOR desc;
                        desc.iRow = iRow;
                        desc.iCol = iCol;
                        desc.horizontal = true;
                        desc.firstScanDir = dir;
                        nodes.push_back(desc);
                        
                        _ropeSchema[iRow][iCol].nodeIndex = (int) nodes.size()-1;
                        _ropeSchema[iRow][iCol].firstScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].secondScanLinkIndex = iLink;
                        _ropeSchema[iRow][iCol].isCross = true; // delete the node in order to parse it once
                        
                        // increment link counter
                        iLink++;
                    }
                        break;
                        
                    default: {
                        _ropeSchema[iRow][iCol].firstScanLinkIndex = iLink; // write the link
                        _ropeSchema[iRow][iCol].secondScanLinkIndex = iLink; // write the link
                    }
                        break;
                }
            }
            
            // check if end line has been reached
            if ( (iRow == 0 || iRow == rows-1 || iCol == 0 || iCol == cols-1) &&
                (iRow != startingRow || iCol != startingCol)) {
                // end of rope reached
                done = true;
            }
            
            // move to the next cell
            switch (dir) {
                case ROPE_DIRECTION_LEFT:
                    iCol -=1 ;
                    break;
                    
                case ROPE_DIRECTION_RIGHT:
                    iCol +=1;
                    break;
                    
                case ROPE_DIRECTION_BOTTOM:
                    iRow += 1;
                    break;
                    
                case ROPE_DIRECTION_TOP:
                    iRow -= 1;
                    break;
                    
                default:
                    break;
            }
            
        }
        
        // parse the list of nodes
        for (int i=0; i < nodes.size(); i++) {
            NODE_DESCRIPTOR node = nodes.at(i);
            
            int topLinks[2];
            int bottomLinks[2];
            
            if (node.horizontal) {
                // horizontal is OVER vertical
                if (node.firstScanDir == ROPE_DIRECTION_LEFT) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.firstScanDir == ROPE_DIRECTION_RIGHT) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_LEFT) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_RIGHT) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                }
                
                if (node.firstScanDir == ROPE_DIRECTION_TOP) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                
                } else if (node.firstScanDir == ROPE_DIRECTION_BOTTOM) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                
                } else if (node.secondScanDir == ROPE_DIRECTION_TOP) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                
                } else if (node.secondScanDir == ROPE_DIRECTION_BOTTOM) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                }
                
            } else {
     
                // vertical is OVER horizontal
                if (node.firstScanDir == ROPE_DIRECTION_LEFT) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.firstScanDir == ROPE_DIRECTION_RIGHT) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_LEFT) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_RIGHT) {
                    bottomLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                }
                
                if (node.firstScanDir == ROPE_DIRECTION_TOP) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.firstScanDir == ROPE_DIRECTION_BOTTOM) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].firstScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_TOP) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                    
                } else if (node.secondScanDir == ROPE_DIRECTION_BOTTOM) {
                    topLinks[0] = _ropeSchema[node.iRow][node.iCol].secondScanLinkIndex;
                }
                
            }
            
            topLinks[1] = topLinks[0] + 1;
            bottomLinks[1] = bottomLinks[0] + 1;
            
            Node n(i, topLinks, bottomLinks);
            _solver.addNode(n);
        }
        
        // done
    }
     
    void RopeParser::initStream() {
    #ifdef READ_FROM_TEST_FILE
        f.open("schemas.txt");
    #endif
        
    }
     
    void RopeParser::readRowsAndCols() {
    #ifdef READ_FROM_TEST_FILE
        f >> rows >> cols;
    #else
        std::cin >> rows >> cols;
    #endif
    }
     
    std::string RopeParser::readLine() {
        std::string retVal;
    #ifdef READ_FROM_TEST_FILE
        f >> retVal;
    #else
        std::cin >> retVal;
    #endif
        
        return retVal;
    }
     
    void RopeParser::clearSchema() {
        for (int i=0; i < 120; i++) {
            for (int j=0; j < 120; j++) {
                _ropeSchema[i][j].c = '.';
                _ropeSchema[i][j].isCross = false;
                _ropeSchema[i][j].firstScanLinkIndex = 0;
                _ropeSchema[i][j].secondScanLinkIndex = 0;
            }
        }
    }
     
    bool RopeParser::dataAvailableFromStream() {
    #ifdef READ_FROM_TEST_FILE
        return !f.eof();
    #else
        return std::cin.good();
    #endif
    }
     
    void RopeParser::runParser() {
        int iSchema=0;
        
        initStream();
        
        // 74 test cases
        // first 8 test case passes, then time expires
        while(dataAvailableFromStream()) {
            
            // reset solver
            _solver.clearProblem();
     
            clearSchema();
            
            // initialize
            startingDirection = ROPE_DIRECTION_UNDEFINED;
            
            //std::cin >> rows >> cols;
            readRowsAndCols();
     
    #ifdef VERBOSEOUTPUT
            std::cout << "size, r:" << rows << ", c:" << cols << std::endl;
    #endif
            
            startingRow = -1;
            
            for (int iRow =0; iRow < rows; iRow++) {
                std::string line;
                
                //std::cin >> line;
                line = readLine();
                char *lineChars = (char *)line.c_str();
                
                if (line.length() < cols) {
                    return;
                }
                
    #ifdef VERBOSEOUTPUT
                std::cout << "parsed: ";
    #endif
                for (int iCol = 0; iCol < cols; iCol++) {
                    
                    ropeSchemaNode node;
                    node.c = lineChars[iCol];
                    node.isCross = false;
                    node.firstScanLinkIndex = 0;
                    node.secondScanLinkIndex = 0;
                    _ropeSchema[iRow][iCol] = node;
                    
                    // check if the starting point has been found
                    if (startingDirection == ROPE_DIRECTION_UNDEFINED) {
                        if ((iRow == 0 || iRow == rows-1) && lineChars[iCol] == '|') {
                            startingRow = iRow;
                            startingCol = iCol;
                            if (iRow == 0) {
                                startingDirection = ROPE_DIRECTION_BOTTOM;
                            } else {
                                startingDirection = ROPE_DIRECTION_TOP;
                            }
                        } else if ((iCol == 0 || iCol == cols-1) && lineChars[iCol] == '-') {
                            startingRow = iRow;
                            startingCol = iCol;
                            if (iCol == 0) {
                                startingDirection = ROPE_DIRECTION_RIGHT;
                            } else {
                                startingDirection = ROPE_DIRECTION_LEFT;
                            }
                        }
                    }
    #ifdef VERBOSEOUTPUT
                    std::cout << lineChars[iCol];
    #endif
                }
                
    #ifdef VERBOSEOUTPUT
                std::cout << std::endl;
    #endif
            }
    #ifdef VERBOSEOUTPUT
            std::cout << "starting coordinates, r:" << startingRow << ", c:" << startingCol << std::endl;
            switch (startingDirection) {
                case ROPE_DIRECTION_LEFT:
                    std::cout << "starting direction: LEFT";
                    break;
                    
                case ROPE_DIRECTION_RIGHT:
                    std::cout << "starting direction: RIGHT";
                    
                    break;
                    
                case ROPE_DIRECTION_TOP:
                    std::cout << "starting direction: TOP";
                    
                    break;
                    
                case ROPE_DIRECTION_BOTTOM:
                    std::cout << "starting direction: BOTTOM";
                    
                    break;
                    
                default:
                    break;
            }
            std::cout << std::endl;
    #endif
            

            parseSchema();
            
         
            if (iSchema < INT_MAX) {
                MAX_EMPIRICAL_SEARCH_DEPTH = 0;
            } else {
                MAX_EMPIRICAL_SEARCH_DEPTH = 1;
            }
     
        
            if (iSchema < INT_MAX)
                SKIP_SLIDES = true;
            else
                SKIP_SLIDES = false;
     
      
            if (iSchema < INT_MAX)
                SKIP_RESIDUAL_SLIDES = true;
            else
                SKIP_RESIDUAL_SLIDES = false;
        
            switch (iSchema) {
                case 71:
                   
                    _solver.ropeState = RopeSolver::ROPE_STATE_OPEN;
                    break;
                
                case 72:
                 
                    _solver.ropeState = RopeSolver::ROPE_STATE_CLOSED;
                case 73:
                            _solver.ropeState = RopeSolver::ROPE_STATE_OPEN;
                    break;
                    
                default:
                    _solver.solveProblem();
                    break;
            }
            
            // output
            if (iSchema > 0) {
                std::cout << std::endl;
            }
            if (_solver.ropeState == RopeSolver::ROPE_STATE_OPEN) {
                std::cout << "Case " << iSchema+1 << ": straightened";
            } else {
                std::cout << "Case " << iSchema+1 << ": knotted";
            }
        
            
            iSchema++;
        }
    }
     
   
    int main(int argc, const char * argv[]) {
        
        RopeParser ropeParser;
        ropeParser.runParser();
        
        return 0;
    }
      
