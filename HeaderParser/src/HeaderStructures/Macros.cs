
namespace BuildTool
{
    static public class Macros
    {
        static public string class_ { get; set; } = "CLASS(";

        static public string struct_ { get; set; } = "STRUCT(";
        static public string function_ { get; set; } = "FUNCTION(";
        static public string property_ { get; set; } = "PROPERTY(";
        static public string enum_ { get; set; } = "ENUM(";

        static public string namespace_ { get; } = @"(?=.*\bnamespace\b)^(?!.*(=|using)).*";
    }
}