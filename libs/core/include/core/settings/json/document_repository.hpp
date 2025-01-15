#pragma once

#include <iosfwd>
#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

namespace vortex::core::settings::json
{

const unsigned DEFAULT_OUTPUT_INDENT = 2u;

class DocumentRepository
{
public:
    DocumentRepository() noexcept = default;

    DocumentRepository(DocumentRepository const&) = delete;
    DocumentRepository& operator=(DocumentRepository const&) = delete;
    DocumentRepository(DocumentRepository &&) = delete;
    DocumentRepository& operator=(DocumentRepository &&) = delete;

    ~DocumentRepository() noexcept = default;

public:
    [[nodiscard]] constexpr unsigned output_indent() const noexcept { return m_output_indent; }
    constexpr void set_output_indent(unsigned output_indent) noexcept
    {
        m_output_indent = output_indent;
    }
    constexpr void reset_output_indent() noexcept
    {
        m_output_indent = DEFAULT_OUTPUT_INDENT;
    }

    [[nodiscard]] bool is_empty() const noexcept { return m_docs.empty(); }
    [[nodiscard]] operator bool() const noexcept { return is_empty(); }
    [[nodiscard]] std::size_t count() const noexcept { return m_docs.size(); }

    [[nodiscard]] auto cbegin() const noexcept { return std::cbegin(m_docs); }
    [[nodiscard]] auto cend() const noexcept { return std::cend(m_docs); }

    void load(std::string const& key, std::istream& is);
    void save(std::string const& key, std::ostream& os);

    [[nodiscard]] bool contains(std::string const& key) const { return m_docs.contains(key); }

    [[nodiscard]] nlohmann::json& get(std::string const& key)
    {
        return m_docs.at(key);
    }
    [[nodiscard]] nlohmann::json& operator[](std::string const& key)
    {
        return get(key);
    }

    void release(std::string const& key) { m_docs.erase(key); }
    void clear() { m_docs.clear(); }

private:
    std::unordered_map<std::string, nlohmann::json> m_docs;

    unsigned m_output_indent = DEFAULT_OUTPUT_INDENT;
};

}
