# 42philosophers
- 食事する哲学者の問題を解くぞ！
- グローバル変数は使えない．
- 表示する時間がチグハグになってはならない．
- 誰かが死んだら即終了．
- みんながお腹いっぱいになったら即終了．
- エラー処理頑張る．

### philo_one
- pthread と pthread_mutex を使ってデッドロックが起きないように工夫しながら，食事する哲学者の問題を解く．
- 哲学者1人が1スレッド．
- mutex は何個でも持てる．

### philo_two
- pthread とカウンティングセマフォとバイナリセマフォを上手に使って，食事する哲学者の類似問題を解く．
- 哲学者1人が1スレッド．
- 哲学者1人に対して1つの専用のセマフォだけが使える．

### philo_three
- fork, waitpid, kill, カウンティングセマフォとバイナリセマフォを上手に使って，食事する哲学者の類似問題を解く．
- 哲学者1人が1プロセス．
- static と関数ポインタの配列と状態遷移を上手に使うとコードが短く書ける．
- 哲学者1人に対して1つの専用のセマフォだけが使える．

## References
- [How to use POSIX semaphores on forked processes in C?](https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c)
- [Multiple child process](https://stackoverflow.com/questions/876605/multiple-child-process)
- [sem_close vs sem_unlink when process terminates](https://stackoverflow.com/questions/9537068/sem-close-vs-sem-unlink-when-process-terminates)
- [並行プログラムと同期](https://www.eidos.ic.i.u-tokyo.ac.jp/~tau/lecture/operating_systems/gen/slides/3-synchronization.pdf)
- [Think OS: A Brief Introduction to Operating Systems](https://greenteapress.com/thinkos/html/index.html)
- [Chapter 11  Semaphores in C](https://greenteapress.com/thinkos/html/thinkos013.html)
- [Chapter 9  Threads](https://greenteapress.com/thinkos/html/thinkos011.html)
- [solareenlo/42pthread_practice](https://github.com/solareenlo/42pthread_practice)
- [Introduction to Parallel Computing Tutorial](https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial)
- [POSIX Threads Programming](https://hpc-tutorials.llnl.gov/posix/)
- [solareenlo/42books](https://github.com/solareenlo/42books)
