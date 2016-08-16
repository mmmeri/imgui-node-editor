#include "Editor.h"
#include "EditorApi.h"


//------------------------------------------------------------------------------
static ax::Editor::Detail::Context* s_Editor = nullptr;


//------------------------------------------------------------------------------
ax::Editor::Context* ax::Editor::CreateEditor()
{
    return reinterpret_cast<ax::Editor::Context*>(new ax::Editor::Detail::Context());
}

void ax::Editor::DestroyEditor(Context* ctx)
{
    if (GetCurrentEditor() == ctx)
        SetCurrentEditor(nullptr);

    auto editor = reinterpret_cast<ax::Editor::Detail::Context*>(ctx);

    delete editor;
}

void ax::Editor::SetCurrentEditor(Context* ctx)
{
    s_Editor = reinterpret_cast<ax::Editor::Detail::Context*>(ctx);
}

ax::Editor::Context* ax::Editor::GetCurrentEditor()
{
    return reinterpret_cast<ax::Editor::Context*>(s_Editor);
}

void ax::Editor::Begin(const char* id)              { s_Editor->Begin(id);                   }
void ax::Editor::End()                              { s_Editor->End();                       }
void ax::Editor::BeginNode(int id)                  { s_Editor->BeginNode(id);               }
void ax::Editor::EndNode()                          { s_Editor->EndNode();                   }
void ax::Editor::BeginHeader(const ImVec4& color)   { s_Editor->BeginHeader(ImColor(color)); }
void ax::Editor::EndHeader()                        { s_Editor->EndHeader();                 }
void ax::Editor::BeginInput(int id)                 { s_Editor->BeginInput(id);              }
void ax::Editor::EndInput()                         { s_Editor->EndInput();                  }
void ax::Editor::BeginOutput(int id)                { s_Editor->BeginOutput(id);             }
void ax::Editor::EndOutput()                        { s_Editor->EndOutput();                 }

bool ax::Editor::Link(int id, int startPinId, int endPinId, const ImVec4& color/* = ImVec4(1, 1, 1, 1)*/, float thickness/* = 1.0f*/)
{
    return s_Editor->DoLink(id, startPinId, endPinId, ImColor(color), thickness);
}

bool ax::Editor::BeginCreate(const ImVec4& color, float thickness)
{
    auto& context = s_Editor->GetItemCreator();

    if (context.Begin())
    {
        context.SetStyle(ImColor(color), thickness);
        return true;
    }
    else
        return false;
}

bool ax::Editor::QueryNewLink(int* startId, int* endId)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    return context.QueryLink(startId, endId) == Result::True;
}

bool ax::Editor::QueryNewLink(int* startId, int* endId, const ImVec4& color, float thickness)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    auto result = context.QueryLink(startId, endId);
    if (result != Result::Indeterminate)
        context.SetStyle(ImColor(color), thickness);

    return result == Result::True;
}

bool ax::Editor::QueryNewNode(int* pinId)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    return context.QueryNode(pinId) == Result::True;
}

bool ax::Editor::QueryNewNode(int* pinId, const ImVec4& color, float thickness)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    auto result = context.QueryNode(pinId);
    if (result != Result::Indeterminate)
        context.SetStyle(ImColor(color), thickness);

    return result == Result::True;
}

bool ax::Editor::AcceptNewItem()
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    return context.AcceptItem() == Result::True;
}

bool ax::Editor::AcceptNewItem(const ImVec4& color, float thickness)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    auto result = context.AcceptItem();
    if (result != Result::Indeterminate)
        context.SetStyle(ImColor(color), thickness);

    return result == Result::True;
}

void ax::Editor::RejectNewItem()
{
    auto& context = s_Editor->GetItemCreator();

    context.RejectItem();
}

void ax::Editor::RejectNewItem(const ImVec4& color, float thickness)
{
    using Result = ax::Editor::Detail::CreateItemAction::Result;

    auto& context = s_Editor->GetItemCreator();

    if (context.RejectItem() != Result::Indeterminate)
        context.SetStyle(ImColor(color), thickness);
}

void ax::Editor::EndCreate()
{
    auto& context = s_Editor->GetItemCreator();

    context.End();
}

bool ax::Editor::BeginDelete()
{
    auto& context = s_Editor->GetItemDeleter();

    return context.Begin();
}

bool ax::Editor::QueryDeletedLink(int* linkId)
{
    auto& context = s_Editor->GetItemDeleter();

    return context.QueryLink(linkId);
}

bool ax::Editor::QueryDeletedNode(int* nodeId)
{
    auto& context = s_Editor->GetItemDeleter();

    return context.QueryNode(nodeId);
}

bool ax::Editor::AcceptDeletedItem()
{
    auto& context = s_Editor->GetItemDeleter();

    return context.AcceptItem();
}

void ax::Editor::RejectDeletedItem()
{
    auto& context = s_Editor->GetItemDeleter();

    context.RejectItem();
}

void ax::Editor::EndDelete()
{
    auto& context = s_Editor->GetItemDeleter();

    context.End();
}

void ax::Editor::SetNodePosition(int nodeId, const ImVec2& position)
{
    s_Editor->SetNodePosition(nodeId, position);
}

ImVec2 ax::Editor::GetNodePosition(int nodeId)
{
    return s_Editor->GetNodePosition(nodeId);
}