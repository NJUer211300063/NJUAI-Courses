package controllers.Heuristics;

import core.game.Observation;
import core.game.StateObservation;
import ontology.Types;
import tools.Vector2d;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: ssamot
 * Date: 11/02/14
 * Time: 15:44
 * This is a Java port from Tom Schaul's VGDL - https://github.com/schaul/py-vgdl
 */
public class WinScoreHeuristic extends StateHeuristic {

    private static final double HUGE_NEGATIVE = -1000.0;
    private static final double HUGE_POSITIVE =  1000.0;

    double initialNpcCounter = 0;

    public WinScoreHeuristic(StateObservation stateObs) {

    }

    public double evaluateState(StateObservation stateObs) {
        boolean gameOver = stateObs.isGameOver();
        Types.WINNER win = stateObs.getGameWinner();
        double rawScore = stateObs.getGameScore();

        if(gameOver && win == Types.WINNER.PLAYER_LOSES)
            return HUGE_NEGATIVE;

        if(gameOver && win == Types.WINNER.PLAYER_WINS)
            return HUGE_POSITIVE;

        return rawScore;

    }
//    public double evaluateState(StateObservation stateObs) {
//        boolean gameOver = stateObs.isGameOver();
//        Types.WINNER win = stateObs.getGameWinner();
//        // 在游戏得分的基础上加一点其他考虑因素
//        double rawScore = stateObs.getGameScore();
//
//        // 赢了或者输了直接返回，不然返回rawScore
//        if(gameOver && win == Types.WINNER.PLAYER_LOSES)
//            return HUGE_NEGATIVE;
//
//        if(gameOver && win == Types.WINNER.PLAYER_WINS)
//            return HUGE_POSITIVE;
//
//        // return rawScore;
//        // 获取rawScore的过程（avatar位置，avatar与目标距离，avatar距离最近的移动和非移动物体，游戏得分，avatar血量）
//        Vector2d avatarPos=stateObs.getAvatarPosition();
//        ArrayList<Observation>[] movingObj=stateObs.getMovablePositions();
//        ArrayList<Observation>[] immovingObj=stateObs.getImmovablePositions();
//        ArrayList<Observation>[] protal=stateObs.getPortalsPositions();
//        Vector2d minImmoving;
//        double immovingDist=9999999;
//        Vector2d minMoving;
//        double movingDist=9999999;
//        Vector2d protalPos=null;
//        double protalDist=0;
//        for(ArrayList<Observation> l:immovingObj) {
//            if(l.size()>0){
//                for(Observation obs:l) {
//                    if(immovingDist>avatarPos.dist(obs.position)) {
//                        minImmoving = obs.position;
//                        immovingDist=avatarPos.dist(obs.position);
//                    }
//                }
//            }
//        }
//        for(ArrayList<Observation> l:movingObj){
//            if(l.size()>0){
//                for(Observation obs:l){
//                    if(movingDist>avatarPos.dist(obs.position)) {
//                        minMoving = obs.position;
//                        movingDist=avatarPos.dist(obs.position);
//                    }
//                }
//            }
//        }
//        if(protal!=null){
//            protalPos=protal[0].get(0).position;
//            protalDist=avatarPos.dist(protalPos);
//        }
//        if(movingDist==0)
//            rawScore += stateObs.getAvatarHealthPoints()+stateObs.getGameScore()-protalDist*100-999
//                    +immovingDist;
//        else
//            rawScore += stateObs.getAvatarHealthPoints()+stateObs.getGameScore()-protalDist*100
//                    +movingDist*10+immovingDist;
//        return rawScore;
//    }


}


