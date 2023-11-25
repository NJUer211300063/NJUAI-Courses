package controllers.Astar;

import controllers.sampleMCTS.SingleTreeNode;
import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

import java.util.ArrayList;
import java.util.PriorityQueue;


public class Agent extends AbstractPlayer {

    private PriorityQueue<Node> openList = new PriorityQueue<>();
    private ArrayList<Node> closeList = new ArrayList<>();
    private ArrayList<StateObservation> visited = new ArrayList<>();
    private StateObservation state;
    private Node last_node = null;
    private ArrayList<Types.ACTIONS> path = new ArrayList<>();
    private boolean is_win = false;
    private int max_depth = 25;


    public Agent(StateObservation so, ElapsedCpuTimer elapsedTimer) {
        this.state = so;
        // return;
    }

    public boolean isInClose(Node obs) {
        for (Node node : this.closeList) {
            if (node.me.equalPosition(obs.me)) {
                return true;
            }
        }
        return false;
    }

    public boolean isInOpen(Node obs) {
        for (Node node : this.openList) {
            if (node.me.equalPosition(obs.me)) {
                return true;
            }
        }
        return false;
    }

    public boolean isInVisited(StateObservation obs) {
        for (StateObservation so : this.visited) {
            if (obs.equalPosition(so))
                return true;
        }
        return false;
    }
    // 返回openlist中的某个node
    public Node getFromOpen(Node obs) {
        for (Node node : this.openList) {
            if (node.me.equalPosition(obs.me)) {
                return obs;
            }
        }
        return null;
    }

    public void AStar(StateObservation stateObs) {
        // 1. 把起始格添加到开启列表。
        Node root_node = new Node(stateObs, null);
        this.openList.add(root_node);
        /*
         * 2.重复如下的工作:
         * a) 寻找开启列表中估量代价F值最低的格子。我们称它为当前格.
         * b) 把它切换到关闭列表。
         * c) 对相邻的4格中的每一个进行如下操作
         * * 如果它不可通过或者已经在关闭列表中，略过它。反之如下。
         * * 如果它不在开启列表中，把它添加进去。把当前格作为这一格的父节点。记录这一格的F,G,和H值。
         * * 如果它已经在开启列表中，用G值为参考检查新的路径是否更好。更低的G值意味着更好的路径。如果是这样，就把这一格的父节点改成当前格，
         * * 并且重新计算这一格的G和F值。如果你保持你的开启列表按F值排序，改变之后你可能需要重新对开启列表排序。
         * d) 停止，当你把目标格添加进了关闭列表(注解)，这时候路径被找到，或者
         * 没有找到目标格，开启列表已经空了。这时候，路径不存在。
         */
//        int depth = 0;
        while (!this.openList.isEmpty()) {
//            depth += 1;
            Node cur_node = this.openList.remove();
            this.closeList.add(cur_node.copy());
            ArrayList<Types.ACTIONS> actions = cur_node.me.getAvailableActions();
            if (!cur_node.me.isGameOver())
                this.last_node = cur_node;
            for (Types.ACTIONS ac : actions) {
                StateObservation stCopy = cur_node.me.copy();
                stCopy.advance(ac);
                Node son = new Node(stCopy, cur_node);
                if (this.isInVisited(stCopy)) continue;
                if (stCopy.isGameOver()) {
                    if (stCopy.getGameWinner() == Types.WINNER.PLAYER_WINS) {
                        this.last_node = son;
                        this.is_win = true;
                        System.out.println("WIN, SCORE: " + stCopy.getGameScore());
                        return;
                    } else continue;
                } else if (isInClose(son)) continue;
                else if (!isInOpen(son)) this.openList.add(son);
                else if (isInOpen(son)) {
                    double new_g = cur_node.g_val + 50;
                    Node son_copy = getFromOpen(son);
                    if (new_g < son_copy.g_val) {
                        openList.remove(son_copy);
                        openList.add(son);
                        break;
                    }
                }
            }
//            if (depth == this.max_depth) {return; }
        }
    }

    public void AStarSearch(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
        double avgTimeTaken = 0;
        double acumTimeTaken = 0;
        long remaining = elapsedTimer.remainingTimeMillis();
        int numIters = 0;

        int remainingLimit = 5;
        while(remaining > 2*avgTimeTaken && remaining > remainingLimit){
            ElapsedCpuTimer elapsedTimerIteration = new ElapsedCpuTimer();
            this.AStar(stateObs);

            numIters++;
            acumTimeTaken += (elapsedTimerIteration.elapsedMillis()) ;

            avgTimeTaken  = acumTimeTaken/numIters;
            remaining = elapsedTimer.remainingTimeMillis();
            //System.out.println(elapsedTimerIteration.elapsedMillis() + " --> " + acumTimeTaken + " (" + remaining + ")");
        }
        this.get_path();
        //System.out.println("-- " + numIters + " -- ( " + avgTimeTaken + ")");

    }

    public void get_path() {
        this.path.clear();
        Node tmp = this.last_node.copy();
        while (tmp.father != null) {
            Types.ACTIONS ac = tmp.me.getAvatarLastAction();
            path.add(ac);
            visited.add(tmp.me);
            System.out.println("path add: " + ac);
            tmp = tmp.father.copy();
        }
        this.openList.clear();
        this.closeList.clear();
    }

    @Override
    public Types.ACTIONS act(StateObservation statsObs, ElapsedCpuTimer elapsedTimer) {
        // System.out.println(this.last_node.me.getAvatarLastAction());
        if (this.last_node == null || path.size() == 0) {
            System.out.println("Begin found!!!");
            this.AStar(statsObs);
            if (this.is_win)
                System.out.println("We founded it!!!");
            else
                System.out.println("False to found!!!");
            this.get_path();
            return null;
        }
        if (path.size() >= 1) {
            Types.ACTIONS action = path.get(path.size() - 1);
            path.remove(path.size() - 1);
            System.out.println("Select action: " + action);
            return action;
        } else {
            System.out.println("There is no selectable action!");
            return null;
        }
    }

}
