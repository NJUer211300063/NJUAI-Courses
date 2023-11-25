package controllers.DepthFirst;

import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import tools.ElapsedCpuTimer;


import java.util.ArrayList;


public class Agent extends AbstractPlayer{
    // 记录搜索的路径
    private static ArrayList<Types.ACTIONS> path;
    // 判断是否找到路径
    private boolean is_found;
    // 记录搜索过的状态
    private static ArrayList<StateObservation> used_state;


    /**
     * Public constructor with state observation and time due.
     * @param so state observation of the current game.
     * @param elapsedTimer Timer for the controller creation.
     */
    public Agent(StateObservation so, ElapsedCpuTimer elapsedTimer){
        path = new ArrayList<>();
        is_found = false;
        used_state = new ArrayList<>();
        used_state.add(so);
    }

    /**
     * Picks an action. This function is called every game step to request an
     * action from the player.
     * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
     * @return An action for the current state
     */
    @Override
    public Types.ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
        // 如果找到,就先dfs
        if(!is_found) {
            dfs(stateObs);
        }
        if (path.size() >= 1) {
            Types.ACTIONS action = path.get(0);
            path.remove(0);
            return action;
        }
        else return null;
    }

    /**
     * 深度优先搜索
     * @param statsObs Observation of the current state.
     */
    public void dfs(StateObservation statsObs) {
        // 如果找到了路径,就不要继续搜索了
        if (is_found)   return;

        ArrayList<Types.ACTIONS> actions =  statsObs.getAvailableActions();

        for (int i = 0; i < actions.size(); i++) {
            Types.ACTIONS action = actions.get(i);
            StateObservation stCopy = statsObs.copy();
            stCopy.advance(action);

            // 判断状态是否重复
            boolean judge = false;
            for (StateObservation so:used_state) {
                if (stCopy.equalPosition(so)) {
                    judge = true;
                    break;
                }
            }
            if (judge)
                continue;

            // 判断游戏是否结束
            if (stCopy.isGameOver()) {
                if (stCopy.getGameWinner() == Types.WINNER.PLAYER_WINS) {
                    path.add(action);
                    is_found = true;
                    return;
                }
                else  continue;
            }

            // 更新状态,继续往下搜索
            used_state.add(stCopy.copy());
            path.add(action);
            dfs(stCopy.copy());

        }

        if (!is_found) {
            if(path.size() >= 1)
                path.remove(path.size() - 1);
        }
    }


}
