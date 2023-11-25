package controllers.Astar;

import core.game.Observation;
import core.game.StateObservation;
import ontology.Types;
import tools.Vector2d;

import java.util.ArrayList;

/**
 * 定义节点类
 */
public class Node implements Comparable<Node>{
    public StateObservation me;
    public Node father;
    public double f_val;
    public double h_val;
    public double g_val;

    public Node() {
        return;
    }

    public Node(StateObservation ob, Node fa) {
        update_father(ob, fa);
    }


    public void update_g(double g) {
        this.g_val = g;
    }

    // 获取节点的h值
    public void get_h() {
        // 赢了h设为无穷小, 否则设为无穷大
        if (this.me.isGameOver()) {
            if (this.me.getGameWinner() == Types.WINNER.PLAYER_WINS)
                this.h_val = Double.NEGATIVE_INFINITY;
            else
                this.h_val = Double.POSITIVE_INFINITY;
            return;
        }

        ArrayList<Observation>[] fixedPositions = this.me.getImmovablePositions();
        ArrayList<Observation>[] movingPositions = this.me.getMovablePositions();
//        System.out.println(fixedPositions);
//        System.out.println(movingPositions);
        Vector2d goal_pos = fixedPositions[1].get(0).position; // 目标的坐标
        Vector2d player_pos = new Vector2d(this.me.getAvatarPosition());// 玩家位置

        // 分为没拿到钥匙和拿到钥匙的情况
        if (this.me.getAvatarType() == 1) {
            Vector2d key_pos = movingPositions[0].get(0).position; //钥匙的坐标
            double x_diff = Math.abs(player_pos.x-key_pos.x);
            double y_diff = Math.abs(player_pos.y-key_pos.y);
            this.h_val = x_diff+y_diff-this.me.getGameScore();
        } else {
            double x_diff = Math.abs(player_pos.x-goal_pos.x);
            double y_diff = Math.abs(player_pos.y-goal_pos.y);
            this.h_val = x_diff+y_diff-this.me.getGameScore();
        }

    }

    //更新父亲节点
    public void update_father(StateObservation me, Node ob) {
        this.me = me.copy();
        if (ob == null) {
            this.get_h();
            this.g_val = 0;
            this.f_val = this.h_val + this.g_val;
            return;
        }
        this.father = ob;
        this.get_h();
        this.g_val = father.g_val + 50;
        this.f_val = this.g_val + this.h_val;
    }

    // 用来进行node类的比较, 用在最小优先队列
    @Override
    public int compareTo(Node o) {
        return (int)(this.f_val - o.f_val);
    }

    // copy节点,防止引用时产生副作用
    public Node copy() {
        return new Node(this.me, this.father);
    }
}
