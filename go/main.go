package main

import (
	"context"
	"flag"
	"fmt"
	"looptest/lib"
	"math/rand"
	"os"
	"path/filepath"
	"runtime/trace"
	"sort"
	"sync"
)

var (
	// 1_0000_0000
	loopMax   int = 0
	loopCnt   int = 0
	traceName string
)

func main() {
	logger := lib.L()
	flag.IntVar(&loopMax, "loopMax", 0, "loopMax")
	flag.IntVar(&loopCnt, "loopCnt", 0, "loopCnt")
	flag.StringVar(&traceName, "traceName", "", "traceName")
	flag.Parse()

	if loopMax == 0 || loopCnt == 0 || traceName == "" {
		lib.L().Error("loopMax and loopCnt must be set")
		flag.Usage()
		return
	}

	foldaPath := "trace"
	traceFileName := traceName + ".out"
	filePath := filepath.Join(foldaPath, traceFileName)

	file, err := os.Create(filePath)
	if err != nil {
		logger.Error("Failed to open file", "err", err)
		return
	}
	defer file.Close()

	if err = trace.Start(file); err != nil {
		logger.Error("Failed to start trace", "err", err)
		return
	}
	defer trace.Stop()

	ctx, task1 := trace.NewTask(context.Background(), "Sequential Loop Task")

	region1 := trace.StartRegion(ctx, "Sequential Loop")
	timer1 := test1(ctx)
	region1.End()
	task1.End()

	logger.Debug("------------------")

	ctx, task2 := trace.NewTask(ctx, "Concurrent Loop Task")
	region2 := trace.StartRegion(ctx, "Concurrent Loop")
	timer2 := test1Concurrent(ctx)
	region2.End()
	task2.End()

	logger.Info("End", "loopMax", loopMax, "loopCnt", loopCnt)
	logger.Info("[Test1] Elapsed MilliSeconds", "ms", timer1.ElapsedMilliSeconds())
	logger.Info("[Test1 Concurrent] Elapsed MilliSeconds", "ms", timer2.ElapsedMilliSeconds())

}

func test1(ctx context.Context) lib.ExeTimer {
	logger := lib.L()

	logger.Info("[Test1] Start Loop", "loopMax", loopMax, "loopCnt", loopCnt)
	wholetimer := lib.MeasureStart()
	for i := 0; i < loopCnt; i++ {
		region := trace.StartRegion(ctx, fmt.Sprintf("Loop [%d]", i))
		func(i int) {
			r := makeRand(i)
			loop(r)
			logger.Info("[Test1] loop done", "i", i)
		}(i)
		region.End()
	}
	wholetimer.MeasureEnd()

	logger.Info("[Test1] All Loop was done", "ms", wholetimer.ElapsedMilliSeconds())
	return *wholetimer
}

func test1Concurrent(ctx context.Context) lib.ExeTimer {
	logger := lib.L()

	logger.Info("[Test1 Concurrent] Start Loop", "loopMax", loopMax, "loopCnt", loopCnt)

	wholetimer := lib.MeasureStart()
	var wg sync.WaitGroup
	for i := 0; i < loopCnt; i++ {
		wg.Add(1)
		go func(i int) {
			defer wg.Done()
			region := trace.StartRegion(ctx, fmt.Sprintf("Loop [%d]", i))
			defer region.End()
			r := makeRand(i)
			loop(r)
			logger.Info("[Test1 Concurrent] loop done", "i", i)
		}(i)
	}
	wg.Wait()
	wholetimer.MeasureEnd()

	logger.Info("[Test1 Concureernt] All Loop was done", "ms", wholetimer.ElapsedMilliSeconds())
	return *wholetimer
}

func makeRand(seed int) *rand.Rand {
	source := rand.NewSource(int64(seed))
	return rand.New(source)
}

func loop(r *rand.Rand) {

	values := make([]int, loopMax)

	for i := 0; i < loopMax; i++ {
		value := r.Int63n(1_0000)
		values[i] = int(value)
	}

	sort.Ints(values)
}
