/*
 * Copyright (C) 2021 magicxqq <xqq@xqq.im>. All rights reserved.
 *
 * This file is part of libaribcaption.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <memory>
#include "renderer/font_provider.hpp"
#include "renderer/font_provider_coretext.hpp"
#include "renderer/font_provider_fontconfig.hpp"

namespace aribcaption {

std::unique_ptr<FontProvider> FontProvider::Create(FontProviderType type, Context& context) {
    switch (type) {
        case FontProviderType::kCoreText:
            return std::make_unique<FontProviderCoreText>(context);
        case FontProviderType::kFontconfig:
            return std::make_unique<FontProviderFontconfig>(context);
        case FontProviderType::kAuto:
        default:
#if defined(_WIN32)
            // TODO: FontProviderDirectWrite
#elif defined(__APPLE__)
            return std::make_unique<FontProviderCoreText>(context);
#else
            return std::make_unique<FontProviderFontconfig>(context);
#endif
    }
}

}  // namespace aribcaption
