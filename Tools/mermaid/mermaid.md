# Mermaid从入门到入土

## 概述

### What

- Mermaid是基于Javascript的绘图工具，用户可以方便快捷地通过代码创建图表
- 项目地址：[mermaid](https://github.com/mermaid-js/mermaid)

### How

- 特定的Mermaid渲染器：[mermaid-live-editor](https://mermaid-js.github.io/mermaid-live-editor)
- 集成了Mermaid渲染功能的Markdown编辑器：`Typora`

- Mermaid图类型

  | **类型** | **关键字**      |
  | -------- | --------------- |
  | 饼状图   | pie             |
  | 流程图   | graph           |
  | 序列图   | sequenceDiagram |
  | 甘特图   | gantt           |
  | 类图     | classDiagram    |
  | 状态图   | stateDiagram    |
  | 旅程图   | journey         |

## 饼状图

### 语法

- 从`pie`关键字开始图表
- 然后使用`title`关键字及其在字符串中的值，为饼图赋予标题。（可选）
- 数据部分
  - 在`" "`内写上分区名
  - 分区名后使用`:`作为分隔符
  - 分隔符后写上数值，最多支持2位小数——数据会以百分比的形式展示

### 实例

```mermaid
pie
    title 为什么总是宅在家里？
    "喜欢宅" : 15
    "天气太热或太冷" : 20
    "穷" : 500
```

## 流程图

### 实例

```mermaid
graph LR
    A[Start] --> B{Is it?};
    B -- Yes --> C[OK];
    C --> D[Rethink];
    D --> B;
    B -- No ----> E[End];
```

### 方向

| **方向** | **关键字**                      |
| -------- | ------------------------------- |
| 从上往下 | `graph`或`graph TB`或`graph TD` |
| 从下往上 | `graph BT`                      |
| 从左往右 | `graph LR`                      |
| 从右往左 | `graph RL`                      |

## 结点

- 无名字的结点：直接写内容，此时结点边框为方形；节点内容不能有空格
- 有名字的结点：节点名后书写内容，内容左右有特定符号，结点边框由符号决定；节点内容可以有空格

> 下面的实例中，没有为graph指定方向，因此默认是从上往下的。但是由于各个结点之前没有箭头，所以他们都处于同一排。

```mermaid
graph
    默认方形
    id1[方形]
    id2(圆边矩形)
    id3([体育场形])
    id4[[子程序形]]
    id5[(圆柱形)]
    id6((圆形))
```

```mermaid
graph
	id1{菱形}
	id2{{六角形}}
	id3[/平行四边形/]
	id4[\反向平行四边形\]
	id5[/梯形\]
	id6[\反向梯形/]
```

## 连线形式

- 直链

```mermaid
graph LR
   A -- text --> B -- text2 --> C
```

- 多重链：可以使用`&`字符，或单个描述

```mermaid
graph 
   a --> b & c--> d
   
   A & B--> C & D
   
    X --> M
    X --> N
    Y --> M
    Y --> N
```

## 连线样式

- 实线箭头：分为无文本箭头和有文本箭头，有文本箭头有2种书写格式

```mermaid
graph LR
a-->b--文本1-->c-->|文本2|d
```

- 粗实线箭头：分为无文本箭头和有文本箭头

```mermaid
graph LR
a==>b==文本==>c
```

- 虚线箭头：分为无文本箭头和有文本箭头

```mermaid
graph LR
a-.->b-.文本.->c
```

- 无箭头线：即以上三种连线去掉箭头后的形式

```mermaid
graph LR
a---b
b--文本1---c
c---|文本2|d
d===e
e==文本3===f
f-.-g
g-.文本.-h
```

- 其他连线：需要将`graph`关键字改为`flowchart`，除了新增加的连线形式外，上面三种线的渲染效果也会不同

```mermaid
flowchart LR
    A o--o B
    B <--> C
    C x--x D
    
    旧连线 --文本--> 也会不同
```

- 延长连线：增加相应字符即可，如下图中的B到E，连线中增加了一个`-`。字符可多次添加。

```mermaid
graph LR
    A[Start] --> B{Is it?};
    B -->|Yes| C[OK];
    C --> D[Rethink];
    D --> B;
    B --->|No| E[End];
```

## 类图

```mermaid
classDiagram
Class01 <|-- AveryLongClass : Cool
<<Interface>> Class01
Class09 --> C2 : Where am i?
Class09 --* C3
Class09 --|> Class07
Class07 : equals()
Class07 : Object[] elementData
Class01 : size()
Class01 : int chimp
Class01 : int gorilla
class Class10 {
  <<service>>
  int id
  size()
}
```

## 状态图

```mermaid
stateDiagram-v2
[*] --> Still
Still --> [*]
Still --> Moving
Moving --> Still
Moving --> Crash
Crash --> [*]
```

## Git图

```mermaid
gitGraph:
options
{
    "nodeSpacing": 150,
    "nodeRadius": 10
}
end
commit
branch newbranch
checkout newbranch
commit
commit
checkout master
commit
commit
merge newbranch
```

## 序列图

```mermaid
sequenceDiagram
Alice->>John: Hello John, how are you?
loop Healthcheck
    John->>John: Fight against hypochondria
end
Note right of John: Rational thoughts!
John-->>Alice: Great!
John->>Bob: How about you?
Bob-->>John: Jolly good!
```

### 甘特图

```mermaid
gantt
    section Section
    Completed :done,    des1, 2014-01-06,2014-01-08
    Active        :active,  des2, 2014-01-07, 3d
    Parallel 1   :         des3, after des1, 1d
    Parallel 2   :         des4, after des1, 1d
    Parallel 3   :         des5, after des3, 1d
    Parallel 4   :         des6, after des4, 1d
```

## 旅程图

```mermaid
journey
  title My working day
  section Go to work
    Make tea: 5: Me
    Go upstairs: 3: Me
    Do work: 1: Me, Cat
  section Go home
    Go downstairs: 5: Me
    Sit down: 3: Me
```

## 其他

- 子图：需要将`graph`关键字改为`flowchart`，在代码段的开始加入`subgraph`，尾部加入`end`

```mermaid
flowchart TB
    c1-->a2
    subgraph one
    a1-->a2
    end
    subgraph two
    b1-->b2
    end
    subgraph three
    c1-->c2
    end
    one --> two
    three --> two
    two --> c2
```

- 注释：在行首加入`%%`即可。

```mermaid
graph LR
%%这是一条注释，在渲染图中不可见
    A[Hard edge] -->|Link text| B(Round edge)
    B --> C{Decision}
    C -->|One| D[Result one]
    C -->|Two| E[Result two]
```

## 参考资料

[Mermaid从入门到入土](https://zhuanlan.zhihu.com/p/355997933)

[MiChuan/Mermaid：以类似于markdown的方式从文本生成图表和流程图 (github.com)](https://github.com/MiChuan/mermaid)