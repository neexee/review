#include <sstream>
#include <string>

#include <Git/AnnotatedDiff.h>
#include <Git/Common.h>
#include <Git/Diff.h>

namespace cliutils {
namespace diff {

enum class Format
{
	Patch,          /**< full git diff */
	PatchHeader,    /**< just the file headers of patch */
	Raw,            /**< like git diff --raw */
	NameOnly,       /**< like git diff --name-only */
	NameStatus      /**< like git diff --name-status */
};

enum class Appearance
{
	Plain,
	Colorized
};

struct PrintOptions
{
	Format format;
	Appearance appearance;
};

enum class ControlSymbol
{
	Red,
	Green,
	Cyan,
	Reset,
	Bold
};

std::string ToString(const git::DiffPtr& diff, const diff::PrintOptions& options);
std::string ToString(const git::AnnotatedDiffPtr& diff, const diff::PrintOptions& options);

//////////////////////////////////////////////////////////////////////////////
// TODO: clean up it somehow
struct PrinterState
{
	PrinterState(const PrintOptions& options);
	std::stringstream stream;
	ControlSymbol symbol;
	Appearance difftype;
};

int ColorPrinter(const git_diff_delta* delta, const git_diff_hunk* hunk,
				 const git_diff_line* line, void* data);
void PrintControlSymbol(PrinterState* state, ControlSymbol symbol);
void PrintLine(const git_diff_line* line, std::stringstream& stream);
git_diff_format_t FormatToInt(Format format);

void PrintDelta(const git::AnnotatedDiffDelta& delta, PrinterState& printer);
void PrintDeltaHeader(const git::AnnotatedDiffDelta& delta, PrinterState& printer);
void PrintLine(const git::AnnotatedDiffLine& line, PrinterState& printer);

} // namespace diff
} // namespace cliutils
