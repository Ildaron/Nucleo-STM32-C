import os
import sys
sys.path.append(os.getcwd())
sys.path.append(os.path.join(os.getcwd(),'installed_mac'))
import brainflow
for board in brainflow.board_shim.BoardIds:
    print(board)
