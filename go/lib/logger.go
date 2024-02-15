package lib

import (
	"log/slog"
	"os"

	"github.com/kohinigeee/mylog/clog"
)

var (
	logger *slog.Logger
	level  *slog.LevelVar
)

func L() *slog.Logger {
	return logger
}

func init() {

	level = new(slog.LevelVar)
	level.Set(slog.LevelDebug)

	handlerOption := slog.HandlerOptions{
		Level: level,
	}
	handler, err := clog.NewCustomTextHandler(os.Stdout,
		clog.WithHandlerOption(&handlerOption))

	if err != nil {
		panic(err)
	}

	logger = slog.New(handler)
}
