# 面向对象

## UML

### 关系

UML 关系主要有：依赖、关联、聚合、组合、实现、继承。

![关系](img/1.png)

### 类图

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

### 用例图

[用例图UML建模](https://www.cnblogs.com/lcword/p/10472040.html#:~:text=UML建模——用例图) 通常包含三个元素：参与者、通信连接（或者关联）和实际的用例，使用 [PlantUML Web Server](https://www.plantuml.com/plantuml) 进行绘图。

- 参与者通常用一个简笔画的人来表示，代表用户或者外部设备，以及使用当前系统的其他系统。
- 通信连接用参与者和用例之间的一条线来表示，代表两者之间存在某种形式的通信。
- 用例用一个椭圆形来表示，再配上适当的描述，代表参与者在系统上执行的各种活动。

![关系](img/2.png)

### 序列图

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

### 状态图

```mermaid
---
title: Simple sample
---
stateDiagram-v2
    [*] --> Still
    Still --> [*]

    Still --> Moving
    Moving --> Still
    Moving --> Crash
    Crash --> [*]

```

### 活动图

```mermaid
   stateDiagram-v2
    state fork_state <<fork>>
      [*] --> receive
      receive --> fork_state
      fork_state --> State2
      State2 --> if_state
      	if_state --> State2: if n < 0
      	if_state --> True : if n >= 0
      fork_state --> State3

      state join_state <<join>>
      True --> join_state
      State3 --> join_state
      join_state --> State4
      State4 --> [*]

```

## 设计模式

|      | 创建型                                   | 结构型                                                       | 行为型                                                       |
| ---- | ---------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 类   | 工厂方法                                 | 适配器                                                       | 解释器<br />模板方法                                         |
| 对象 | 抽象工厂<br />生成器<br />原型<br />单例 | 适配器<br />桥接<br />组合<br />装饰<br />外观<br />享元<br />代理 | 责任链<br />命令<br />解释器<br />迭代器<br />中介者<br />备忘录<br />观察者<br />状态<br />策略<br />模板方法<br />访问者 |

## reference

[时序图 | Mermaid 中文网 (nodejs.cn)](https://mermaid.nodejs.cn/syntax/sequenceDiagram.html)

[PlantUML_Language_Reference_Guide](https://pdf.plantuml.net/1.2019.9/PlantUML_Language_Reference_Guide_zh.pdf#:~:text=另外,你还能用<- 和<--,这不影响绘图,但可以提高可读性。.)
