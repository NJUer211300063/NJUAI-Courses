package controllers.LimitedDepthFirst;

import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import tools.ElapsedCpuTimer;
import core.game.Observation;

import java.security.ProtectionDomain;
import java.util.ArrayList;
import tools.Vector2d;

public class Agent extends AbstractPlayer {
    private int max_depth = 3;
    private int max_score = 1000;
    // 是否找到钥匙
    private boolean is_getkey = false;
    Vector2d keypos;
    // 记录搜索过的状态
    private static ArrayList<StateObservation> used_state = new ArrayList<>();


    public Agent(StateObservation so, ElapsedCpuTimer elapsedTimer) {
        ArrayList<Observation>[] movingPositions = so.getMovablePositions();
        keypos = movingPositions[0].get(0).position; //钥匙的坐标
        // return;
    }


    @Override
    public Types.ACTIONS act(StateObservation statsObs, ElapsedCpuTimer elapsedTimer) {
        used_state.add(statsObs);
        ArrayList<Types.ACTIONS> actions = statsObs.getAvailableActions();


        // 获取评分最高的action
        int max_value = -1;
        Types.ACTIONS selected_action = null;
        for (Types.ACTIONS ac : actions) {
            StateObservation stCopy = statsObs.copy();
            stCopy.advance(ac);
            int cur_value = dfs_getscore(stCopy, 1);
            if (cur_value > max_value) {
                max_value = cur_value;
                selected_action = ac;
            }
        }

        if (selected_action == null)
            System.out.println("action is null!");

        System.out.println("---------------------------");
        System.out.println("可选择的actions: " + actions);
        System.out.println("选择这个action: " + selected_action);
        System.out.println("max_value: " + max_value);
        System.out.println("---------------------------");

        return selected_action;
    }

    private int dfs_getscore(StateObservation statsObs, int depth) {
        // System.out.println(depth);
        // 判断游戏是否结束
        if (statsObs.isGameOver()) {
            // 赢了就返回一个很大的分数,输了返回0
            if (statsObs.getGameWinner() == Types.WINNER.PLAYER_WINS)
                return max_score;
            else
                return 0;
        }

        for (StateObservation so : used_state) {
            if (statsObs.equalPosition(so)) {
                return 0;
            }
        }

        // 叶子结点
        if (depth == max_depth)
            return eval(statsObs);


        // 继续往下搜索
        used_state.add(statsObs);
        if (statsObs.getAvatarPosition().equals(keypos))
            is_getkey = true;
        int value = -1;
        ArrayList<Types.ACTIONS> actions = statsObs.getAvailableActions();
        for (Types.ACTIONS ac : actions) {
            StateObservation stCopy = statsObs.copy();
            stCopy.advance(ac);
            int new_value = dfs_getscore(stCopy, depth + 1);
            if (new_value > value) {
                value = new_value;
            }
        }

        used_state.remove(used_state.size() - 1);
        is_getkey = false;
        return value;

    }

    private int eval(StateObservation stateObs) {
        ArrayList<Observation>[] fixedPositions = stateObs.getImmovablePositions();
        ArrayList<Observation>[] movingPositions = stateObs.getMovablePositions();
        Vector2d goalpos = fixedPositions[1].get(0).position; // 目标的坐标
        Vector2d playerpos = new Vector2d(stateObs.getAvatarPosition());// 玩家位置
        //int distance1 = (int)(Math.abs(playerpos.x - goalpos.x) + Math.abs(playerpos.y - goalpos.y)); // 玩家到目标的距离
        //int distance2 = (int)(Math.abs(goalpos.x - keypos.x) + Math.abs(goalpos.y - keypos.y)); // 玩家到钥匙的距离
        // 如果找到钥匙,distance定义为玩家到目标的距离
        double distance1 = playerpos.dist(goalpos);
        double distance2 = playerpos.dist(keypos);
        if (is_getkey) {
            System.out.println("get key!");
            return max_score - (int) distance1;
        } else {
            return max_score - (int) distance1 - (int) distance2;
        }

    }
}


