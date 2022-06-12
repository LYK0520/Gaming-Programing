SFML贪吃蛇——走马灯版本

我们亲爱的仕爷要求我们给贪吃蛇加一点新功能，还要要求在评论区里面发够五篇小文章。这这这...对于一个即将面临期末考试的孩子是一个多大的伤害啊。（bushi）因为之前也出过一个贪吃蛇的新功能的讲解了，所以这次也就不做同样的内容这样子会让人觉得很没有意思欸，所以在我们大户人家的讨论之下，我们决定把整活的目标投向了上个学期的走马灯。

不过，在介绍走马灯功能的实现之前，请先容许我简单的讲解一下我作业里面前两个小功能的代码哈~

- 实现文字界面的优化，为文字增加更加醒目的白边为后面变场景的颜色做准备
  - setOutlineColor的功能主要是为了实现描边的效果 粗细 颜色等等需要注意的是记得在每次绘制完成之后要把粗细调整回来哈~不然的话可能会导致不想要增加描边的部分也加入了描边的队列。
  - ![1654436960612](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654436960612.png)
  - 代码的实现界面如下：
  - ![1654437270902](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437270902.png)

- 通过调整代码逻辑实现长按任意一个方向键后贪吃蛇会增加移动速率，提高游戏的可玩性
  - 在普通模式和步进模式下均通过stillpress的标志来更改游戏逻辑以此达到加速贪吃蛇行进速率的效果
  - ![1654437472831](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437472831.png)
  - 此处代码比较冗余，不过我不想调整了，基本可以压缩到几行以内的
  - ![1654437601961](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437601961.png)

- 增加了走马灯的效果，每次达到50分的整数倍就会开启一次走马灯效果开始为玩家庆祝~
  - 好的接下来就是我们走马灯的代码演示
  - ![1654437674748](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437674748.png)
  - ![1654437710296](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437710296.png)
  - ![1654437739985](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654437739985.png)
  - 首先我们并不希望在0分刚开始的时候就开始走马灯（不要问我为什么，我觉得这样子不好看）所以下面是最基本的判断条件
  - ![1654438381169](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654438381169.png)
  - scorejudgeflag == false是为了不要每次达到这要求的时候就重复执行，这样的方式会导致走马灯一直在闪烁也会影响到游戏的体验
  - score != scoreed这条判断是为了防止在一直50分的时候，一直满足条件在闪烁走马灯后继续闪烁
  - 值得注意的是看上去两个判断似乎差不多，不过它们的含义是截然不同的大家可以好好去体会一下
  - ![1654438779375](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\1654438779375.png)
  - 上述代码是为了让走马灯响应0.5S的事件
  - 其他都是一些细枝末节的操作了，这里就不进行更多的讲解了，所有的代码以及视频通过压缩包的方式上传，也可以通过游览[LYK0520/Gaming-Programing (github.com)](https://github.com/LYK0520/Gaming-Programing)看到我的所有代码数据。