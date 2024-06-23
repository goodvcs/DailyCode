class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [set() for _ in range(9)]
        columns = [set() for _ in range(9)]
        boxes = [set() for _ in range(9)]

        for r in range(9):
            for c in range(9):
                n = board[r][c]
                if(n != "."):
                    if(n in rows[r]):
                        return False
                    rows[r].add(n)
                    if(n in columns[c]):
                        return False
                    columns[c].add(n)
                    b = r//3*3 + c//3
                    if(n in boxes[b]):
                        return False
                    boxes[b].add(n)
        return True
