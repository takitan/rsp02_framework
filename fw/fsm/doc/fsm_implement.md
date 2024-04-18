# FSMの実装方法
## はじめに
OS/02の状態(State)は、必要最小限の記述だけで本格的なFSM動かすことができる。

Entry,Execute,Exitモデルは、FSMの中でも極めて汎用的なモデルであるため、このモデルに設計を落とし込むことができれば、どのような状態も記述することができる。

反面、Entry、Exitは不要なことも多いのも事実であり、その場合は***実装しなければ良い***、なにも処理しない動作を記述したのと同様の処理となる。

## 状態の記述方法
1. 状態に割り振られるStateID（ユニーク）と状態名(ユニークでなくても良い)を決める
	StateID → StateHoge
	状態名 → StateHoge
	とする
StateIDについては、別の場所で定義されているはずなので、その定義に追記する。

2. 状態クラスを記述するファイルを用意する
	状態名 = クラス名 = ファイル名であったほうがわかりやすいため、StateHoge.hppに下記を記述する

	```
	StateHoge.hpp
	
	#pragma once
	#include <cstdio>
	#include "fw/fsm/StateBase.hpp"
	#include "fw/logger/Logger.hpp"
	#include "GlobalDefine.hpp"
	#include "fw/fsm/StateFactory.hpp"

	class InitialState1 : public rsp::rsp02::fw::fsm::StateBase<StateID>
	{
	using StopWatch = rsp::rsp02::fw::time::StopWatch;
	template<size_t N>
	using TinyEvent = rsp::rsp02::fw::fsm::TinyEvent<N>;

	public:
		InitialState1() :
			StateBase(StateID::StateHoge, "StateHoge"){}

	private:
		void Entry()
		{
		}

		IState* Execute()
		{
			return next;
		}

		void Exit()
		{
		}
	};
	```
	#includeはおまじないだと思って受け入れてください
	次に、各処理を実装する。

	1. `void Entry()`に、この状態に遷移してきた最初の1回だけ実行したい処理を実装する
	1. `IState* Execute()`に、この状態にいる間常に実行したい処理を実装する
	1. `void Exit()`に、別状態に遷移する時に1回だけ実行したい処理を実装する