#include <map>
#include <iostream>

#include <Git/Commit.h>
#include <Utils/Utils.h>

#include <Cli/DiffFormat.h>

namespace cliutils {
namespace diff {
namespace {

typedef std::string SymbolCode;
// clang-format off
const std::map<ControlSymbol, SymbolCode> control_symbol_map =
{
	{ ControlSymbol::Red,    "\033[31m" },
	{ ControlSymbol::Green,  "\033[32m" },
	{ ControlSymbol::Cyan,   "\033[36m" },
	{ ControlSymbol::Reset,  "\033[m"   },
	{ ControlSymbol::Bold,   "\033[1m"  },
};

const std::map<Format, git_diff_format_t> format_map =
{
	{ Format::Patch,        GIT_DIFF_FORMAT_PATCH        },
	{ Format::PatchHeader,  GIT_DIFF_FORMAT_PATCH_HEADER },
	{ Format::Raw,          GIT_DIFF_FORMAT_RAW          },
	{ Format::NameOnly,     GIT_DIFF_FORMAT_NAME_ONLY    },
	{ Format::NameStatus,   GIT_DIFF_FORMAT_NAME_STATUS  }
};

const std::map<int, ControlSymbol> line_status_map =
{
	{ GIT_DIFF_LINE_CONTEXT,    ControlSymbol::Reset },
	{ GIT_DIFF_LINE_ADDITION,   ControlSymbol::Green },
	{ GIT_DIFF_LINE_DELETION,   ControlSymbol::Red   },
	{ GIT_DIFF_LINE_ADD_EOFNL,  ControlSymbol::Green },
	{ GIT_DIFF_LINE_DEL_EOFNL,  ControlSymbol::Red   },
	{ GIT_DIFF_LINE_FILE_HDR,   ControlSymbol::Bold  },
	{ GIT_DIFF_LINE_HUNK_HDR,   ControlSymbol::Cyan  },
	{ GIT_DIFF_LINE_BINARY,     ControlSymbol::Reset }
};

// clang-format on
} // namespace

//////////////////////////////////////////////////////////////////////////////

PrinterState::PrinterState(const PrintOptions& options)
: difftype(options.appearance)
{
	if (options.appearance == Appearance::Colorized)
	{
		symbol = ControlSymbol::Reset;
		stream << control_symbol_map.at(ControlSymbol::Reset);
	}
}

std::string ToString(const git::DiffPtr& diff, const PrintOptions& options)
{
	PrinterState printer_state(options);

	git::CheckSuccess("displaying diff ",
		git_diff_print,
		*(diff->Pointer()), FormatToInt(options.format), &diff::ColorPrinter, &printer_state);

	if (options.appearance == Appearance::Colorized)
		printer_state.stream << control_symbol_map.at(ControlSymbol::Reset);
	return printer_state.stream.str();
}

int ColorPrinter(const git_diff_delta* /*delta*/, const git_diff_hunk* /*hunk*/,
		const git_diff_line* line, void* payload)
{
	PrinterState* state = static_cast<PrinterState*>(payload);
	ControlSymbol symbol = line_status_map.at(line->origin);
	PrintControlSymbol(state, symbol);
	PrintLine(line, state->stream);
	return 0;
}

void PrintControlSymbol(PrinterState* state, ControlSymbol symbol)
{
	if (state->difftype != Appearance::Colorized)
	{
		return;
	}

	if (symbol != state->symbol)
	{
		if (state->symbol == ControlSymbol::Bold || symbol == ControlSymbol::Bold)
		{
			state->stream << control_symbol_map.at(ControlSymbol::Reset);
		}
		state->stream << control_symbol_map.at(symbol);
		state->symbol = symbol;
	}
}

void PrintLine(const git_diff_line* line, std::stringstream& stream)
{
	if (line->origin == GIT_DIFF_LINE_CONTEXT ||
		line->origin == GIT_DIFF_LINE_ADDITION ||
		line->origin == GIT_DIFF_LINE_DELETION)
	{
		stream << line->origin;
	}
	stream.write(line->content, line->content_len);
}

git_diff_format_t FormatToInt(Format format)
{
	return format_map.at(format);
}

//////////////////////////////////////////////////////////////////////////////

std::string ToString(const git::AnnotatedDiffPtr& diff, const diff::PrintOptions& options)
{
	PrinterState printer_state(options);
	for (const auto& delta: diff->Deltas())
	{
		PrintDelta(delta, printer_state);
	}
	if (options.appearance == Appearance::Colorized)
		printer_state.stream << control_symbol_map.at(ControlSymbol::Reset);
	return printer_state.stream.str();
}

void PrintDelta(const git::AnnotatedDiffDelta& delta, PrinterState& printer)
{
	PrintDeltaHeader(delta, printer);
	for (const auto& line: delta.Lines())
	{
		PrintLine(line, printer);
	}
}

void PrintDeltaHeader(const git::AnnotatedDiffDelta& delta, PrinterState& printer)
{
	printer.stream << "--- " << delta.OldFile().Path() << std::endl;
	printer.stream << "+++ " << delta.NewFile().Path() << std::endl;
}

void PrintLine(const git::AnnotatedDiffLine& line, PrinterState& printer)
{
	ControlSymbol symbol = line_status_map.at(git::ToChar(line.LineType()));
	PrintControlSymbol(&printer, symbol);

	if (line.LineType() == git::DiffLineType::Context ||
		line.LineType() == git::DiffLineType::Addition ||
		line.LineType() == git::DiffLineType::Deletion)
	{
		printer.stream << git::ToChar(line.LineType());
	}
	auto commit_id = line.CommitId();
	git::Commit commit(commit_id, line.Blame()->Repo());
	printer.stream << commit_id.ShortHex() << " [" << commit.Summary() << "] "
		<< line.Content();
}

} // namespace diff
} // namespace cliutils
